#include "net_work.h"
#include "log.h"
#include "malloc.h"
#include "mq.h"
#include "util.h"
#include "server_thread.h"

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>

#include "queue.h"

#define MESSAGE_LEN_SIZE 4
#define IO_MAX_MESSAGE_SIZE 4096
#define MAX_CONNECT 5
#define SERVANT_TYPE long

// 内部服务器间连接的数据
struct socket_internal_t {
	struct bufferevent *bev;
	socket_t fd;
	SERVANT_TYPE servant_prefix;
	TAILQ_ENTRY(socket_internal_t) entry;
};

TAILQ_HEAD(, socket_internal_t) si_mgr;

struct callback_t {
	net_work_callback nw_cb;
	void *param;
};

static char address[MAX_CONNECT][24];
static char port[MAX_CONNECT][8];
static char prefix[MAX_CONNECT][10];
static struct sockaddr_in sin[MAX_CONNECT];
int px[MAX_CONNECT];

static callback_t serverconnected;
static callback_t clientclose;

static int client_conn = 0;
static int server_conn = 0;
int self_servant_prefix = 0;

struct event_base *BASE = NULL;

void read_helper(struct bufferevent *bev)
{
	char buf_len[MESSAGE_LEN_SIZE] = {0};
	bufferevent_read(bev, buf_len, MESSAGE_LEN_SIZE);
	log_debug("buf_len (%s)", buf_len);
	size_t total_len = 0;
	if (strcmp(buf_len, "RGST") == 0) {
		total_len = 6;
	} else {
		total_len = atoi(buf_len);
	}

    int each_recv_len;
    int recv_len = 0;
	char *message = (char *)Malloc(total_len+1);
	memset(message, 0, total_len+1);

	while (total_len > 0) {
		if (total_len >= IO_MAX_MESSAGE_SIZE) {
			each_recv_len = bufferevent_read(bev, message+recv_len, IO_MAX_MESSAGE_SIZE);
			// assert(each_recv_len == IO_MAX_MESSAGE_SIZE); 	// 不等则可能是丢包了
		} else {
			each_recv_len = bufferevent_read(bev, message+recv_len, total_len);
			log_debug("message(%s) each_recv_len(%d) total_len(%d)", message, each_recv_len, total_len);
			// assert(each_recv_len == total_len);
		}
		recv_len += each_recv_len;
		total_len = total_len - recv_len;
		if (recv_len == 0) break;
		recv_len = 0;
	}

	switch(buf_len[0]) {
		case 'R':
			{
				struct socket_internal_t *st = (struct socket_internal_t *)Malloc(sizeof(struct socket_internal_t));
				memset(st, 0, sizeof(struct socket_internal_t));
				st->fd = bufferevent_getfd(bev);
				st->bev = bev;
				st->servant_prefix = strtol(&message[4], NULL, 16);
				log_info("servant_prefix(0x%04X) register success.", st->servant_prefix);
				TAILQ_INSERT_TAIL(&si_mgr, st, entry);
				Free(message);
			}
			break;
		default:
			mq_push(bev, message);
	}	
}

void read_cb(struct bufferevent *bev, void *userdata)
{
    read_helper(bev);
}

static void event_cb(struct bufferevent *bev, short events, void *userdata)
{
	if (events & BEV_EVENT_EOF) {
		socket_t fd = bufferevent_getfd(bev);
		log_debug("Connection closed, fd = %d.", fd);
		struct socket_internal_t *st;
		TAILQ_FOREACH(st, &si_mgr, entry) {
			if (st->fd == fd) {
				log_debug("servant_prefix(0x%04X) disconnected", st->servant_prefix);
				TAILQ_REMOVE(&si_mgr, st, entry);
				break;
			}
		}

		clientclose.nw_cb(fd, clientclose.param);

		-- client_conn;
	}

	bufferevent_free(bev);
}

void accepted_cb(struct evconnlistener *listener, socket_t fd,
	struct sockaddr *address, int socklen, void *userdata)
{
	struct event_base *base = evconnlistener_get_base(listener);
	struct bufferevent *bev = bufferevent_socket_new(
		base, fd, BEV_OPT_CLOSE_ON_FREE);

	bufferevent_setcb(bev, read_cb, NULL, event_cb, NULL);
	bufferevent_enable(bev, EV_READ|EV_WRITE);

	++ client_conn;
}

void *run_thread(void *userdata)
{
	struct evconnlistener *listener = (struct evconnlistener *)userdata;
	struct event_base *base = evconnlistener_get_base(listener);
	event_base_dispatch(base);
	evconnlistener_free(listener);
	event_base_free(base);

	exit_thread();

	return NULL;
}

static void set_tcp_no_delay(socket_t fd)
{
	int one = 1;
	setsockopt(fd, IPPROTO_TCP, TCP_NODELAY,
  		&one, sizeof one);
}

static void connect_eventcb(struct bufferevent *bev, short events, void *userdata)
{
	int *servant_prefix = (int *)userdata;
	if (events & BEV_EVENT_EOF) {
		socket_t fd = bufferevent_getfd(bev);
		struct socket_internal_t *st;
		TAILQ_FOREACH(st, &si_mgr, entry) {
			if (st->fd == fd) {
				-- server_conn;
				log_debug("servant_prefix(0x%04X) disconnected", st->servant_prefix);
				bufferevent_free(st->bev);
				st->bev = NULL;
				TAILQ_REMOVE(&si_mgr, st, entry);
				break;
			}
		}

	} else if (events & BEV_EVENT_CONNECTED) {
		++ server_conn;
		socket_t fd = bufferevent_getfd(bev);
		set_tcp_no_delay(fd);
		struct socket_internal_t *st = (struct socket_internal_t *)Malloc(sizeof(struct socket_internal_t));
		st->fd = fd;
		st->bev = bev;
		st->servant_prefix = *servant_prefix;
		TAILQ_INSERT_TAIL(&si_mgr, st, entry);
		log_debug("server_conn(%d) servant_prefix(0x%04X) success", server_conn, *servant_prefix);

		char send_buf[11] = "RGST";
		char sp[7] = {0};
		sprintf(sp, "0x%04X", self_servant_prefix);
		strcpy(&send_buf[4], sp);
		bufferevent_write(bev, send_buf, sizeof(send_buf));
		serverconnected.nw_cb(fd, serverconnected.param);
	} else if (events & BEV_EVENT_ERROR) {
		log_debug("cant connect to servant_prefix(0x%04X).", *servant_prefix);
	}
}

void net_work_connect(const char *endpointlist)
{
	if (endpointlist) {
		// 需要连接对端服务器
		server_conn = ch_apear_times(endpointlist, ';') + 1;
		char left[256] = {0};
		char right[256] = {0};
		char port_prefix[16] = {0};
		char epl[64] = {0};
		

		strcpy(epl, endpointlist);
		int i = 0;
		do {
			struct bufferevent *bev = bufferevent_socket_new(BASE, -1, BEV_OPT_CLOSE_ON_FREE);

			str_split(epl, left, right, ';');
			memset(address[i], 0, sizeof(address[i]));
			str_split(left, address[i], port_prefix, ':');
			memset(port[i], 0, sizeof(port[i]));
			memset(prefix[i], 0, sizeof(prefix[i]));
			str_split(port_prefix, port[i], prefix[i], ':');
			memset(&sin[i], 0, sizeof(sin[i]));
			sin[i].sin_family = AF_INET;
			sin[i].sin_addr.s_addr = inet_addr(address[i]);
			sin[i].sin_port = htons(atoi(port[i]));
			px[i] = strtol(prefix[i], NULL, 16);

		    if (bufferevent_socket_connect(bev,
		          (struct sockaddr *)&sin[i], sizeof(struct sockaddr_in)) < 0) {
				bufferevent_free(bev);
				bev = NULL;
				log_debug("connect_socket: error connect");
				exit(1);
			}
			bufferevent_setcb(bev, read_cb, NULL, connect_eventcb, &px[i]);
			bufferevent_enable(bev, EV_READ|EV_WRITE);

			memset(epl, 0, sizeof(epl));
			strcpy(epl, right);
			memset(left, 0, sizeof(left));
			memset(right, 0, sizeof(right));
			// memset(address, 0, sizeof(address));
			// memset(port, 0, sizeof(port));
			// memset(prefix, 0, sizeof(prefix));
			memset(port_prefix, 0, sizeof(port_prefix));
			++ i;
		}while( i < server_conn);
	}
}

void net_work_init()
{
	evthread_use_pthreads();
	BASE = event_base_new();
	TAILQ_INIT(&si_mgr);
}

void net_work_run(const char *address, int port, const char *endpointlist, int prefix)
{
	self_servant_prefix = prefix;
	net_work_connect(endpointlist);
	struct sockaddr_in listener_sin;
	memset(&listener_sin, 0, sizeof(listener_sin));
	listener_sin.sin_family = AF_INET;
	listener_sin.sin_addr.s_addr = inet_addr(address);
	listener_sin.sin_port = htons(port);
	struct evconnlistener *listener;
	listener = evconnlistener_new_bind(BASE, accepted_cb, NULL,
	    LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,
	    (struct sockaddr*)&listener_sin, sizeof(listener_sin));
	if (!listener) {
		log_error("Couldn't create listener");
		exit(1);
	}

	pthread_t t_id;
	create_thread(&t_id, run_thread, listener);
}

void net_work_reg_onclientclose(net_work_callback onclientclose_cb, void *userdata)
{
	clientclose.nw_cb = onclientclose_cb;
	clientclose.param = userdata;
}

void net_work_reg_onserverconnected(net_work_callback onserverconnected_cb, void *userdata)
{
	serverconnected.nw_cb = onserverconnected_cb;
	serverconnected.param = userdata;
}

// 得连接客户端数量
int get_client_conn()
{
	return client_conn;
}

// 得连接对端服务器数量
int get_server_conn()
{
	return server_conn;
}