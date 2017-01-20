#include "NetWork.hpp"
#include "log.h"
#include "util.h"
#include "Memory.hpp"

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>

#include <iostream>

NetWork::NetWork(struct server_config_t *sc)
{
	server_config = sc;
	// tm = Tm;
	// mq = Mq;
	// evthread_use_pthreads();
	// base = event_base_new();
	// client_conn_count = 0;
	// server_conn_count = 0;
}

NetWork::~NetWork()
{
}

/*
	void NetWork::InsertClientConn(socket_t fd, struct bufferevent *bev)
	{
		netClientConnMap.insert(NetClientConnMap::value_type(fd, NEW NetConn(bev, fd)));
		++ client_conn_count;
	}

	bool NetWork::RemoveClientConn(socket_t fd)
	{
		NetClientConnMap::iterator it = netClientConnMap.begin();
		for (it; it != netClientConnMap.end(); it++) {
			if (it->first == fd) {
				netClientConnMap.erase(it);
				-- client_conn_count;

				// TODO Interface 通知出去
				return true;
			}
		}

		return false;
	}

	void NetWork::event_cb(struct bufferevent *bev, short events, void *userdata)
	{
		NetWork *n = (NetWork *)userdata;

		if (events & BEV_EVENT_EOF) {
			socket_t fd = bufferevent_getfd(bev);
			log_debug("Connection closed, fd = %d.", fd);
			n->RemoveClientConn(fd);
		}

		bufferevent_free(bev);
	}

	void NetWork::listener_cb(struct evconnlistener* listener, socket_t fd, struct sockaddr* sa, int socklen, void* user_data)
	{

		struct event_base *_base = evconnlistener_get_base(listener);
		struct bufferevent *bev = bufferevent_socket_new(
			_base, fd, BEV_OPT_CLOSE_ON_FREE);

		bufferevent_setcb(bev, read_cb, NULL, event_cb, user_data);
		bufferevent_enable(bev, EV_READ|EV_WRITE);

		InsertClientConn();
	}

	void NetWork::read_cb(struct bufferevent *bev, void *userdata)
	{
		NetWork *n = (NetWork *)userdata;

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
		char *message = NEW char[total_len];

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
					socket_t fd = bufferevent_getfd(bev);
					int prefix = strtol(&message[4], NULL, 16);
					n->netServerConnMap.insert(NetServerConnMap::value_type(prefix, NEW NetConn(bev, fd, prefix)));
					log_info("servant_prefix(0x%04X) register success.", prefix);
					DELETE message;
				}
				break;
			default:
				{
					n->mq->PushMessage(message);
				}
		}
	}

	void NetWork::connect_eventcb(struct bufferevent *bev, short events, void *userdata)
	{
		char *prefix = (char *)userdata;
		if (events & BEV_EVENT_EOF) {
			log_debug("disconnected %s", prefix);
		} else if (events & BEV_EVENT_CONNECTED) {
			log_debug("connected %s", prefix);
		} else if (events & BEV_EVENT_ERROR) {
			log_debug("error %s", prefix);
		}
	}

	void NetWork::ConnectServer()
	{
		if (server_config->endpointlist) {
			server_conn_count = ch_apear_times(server_config->endpointlist, ';') + 1;
			int i;
			char left[256] = {0};
			char right[256] = {0};
			char port_prefix[16] = {0};
			char epl[64] = {0};
			strcpy(epl, server_config->endpointlist);
			for (i = 0; i < server_conn_count; i ++) {

				str_split(epl, left, right, ';');
				memset(address[i], 0, sizeof(address[i]));
				str_split(left, address[i], port_prefix, ':');
				memset(port[i], 0, sizeof(port[i]));
				memset(prefix[i], 0, sizeof(prefix[i]));
				str_split(port_prefix, port[i], prefix[i], ':');

				// EndpointServer es(address[i], atoi(port[i]), strtol(prefix[i], NULL, 16));
				// endpointServerList.push_back(es);

				memset(&sin[i], 0, sizeof(sin[i]));
				sin[i].sin_family = AF_INET;
				sin[i].sin_addr.s_addr = inet_addr(address[i]);
				sin[i].sin_port = htons(atoi(port[i]));

				memset(epl, 0, sizeof(epl));
				strcpy(epl, right);
				memset(left, 0, sizeof(left));
				memset(right, 0, sizeof(right));
				// memset(address, 0, sizeof(address));
				// memset(port, 0, sizeof(port));
				// memset(prefix, 0, sizeof(prefix));
				memset(port_prefix, 0, sizeof(port_prefix));
			}

			for (i = 0; i < server_conn_count; i++) {
				std::cout << prefix[i] << " " << sin[i].sin_addr.s_addr << " " << sin[i].sin_port << std::endl;
				struct bufferevent *bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
				if (bev == NULL)
			    {
			        log_error("bufferevent_socket_new failed.");
			        exit(1);
			    }
				if (bufferevent_socket_connect(bev,
			          (struct sockaddr *)&sin[i], sizeof(sin[i])) < 0) {
					bufferevent_free(bev);
					bev = NULL;
					log_debug("connect_socket: error connect");
					exit(1);
				}
				bufferevent_setcb(bev, read_cb, NULL, connect_eventcb, (void *)&prefix[i]);
				bufferevent_enable(bev, EV_READ|EV_WRITE);
			}
		}
	}
*/

void NetWork::OnClientClose(socket_t fd, void *userdata)
{
	std::cout << "OnClientClose fd = " << fd << std::endl;
}

void NetWork::OnServerConnected(socket_t fd, void *userdata)
{
	std::cout << "OnServerConnected fd = " << fd << std::endl;
}

void NetWork::Start()
{
	net_work_init();
	net_work_reg_onclientclose(OnClientClose, this);
	net_work_reg_onserverconnected(OnServerConnected, this);

	net_work_run(server_config->address, server_config->port, 
		server_config->endpointlist, server_config->prefix);

	// ConnectServer();

	// struct sockaddr_in listener_sin;
	// memset(&listener_sin, 0, sizeof(listener_sin));
	// listener_sin.sin_family = AF_INET;
	// listener_sin.sin_addr.s_addr = inet_addr(server_config->address);
	// listener_sin.sin_port = htons(server_config->port);
	// struct evconnlistener *listener;
	// listener = evconnlistener_new_bind(base, listener_cb, this,
	//     LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,
	//     (struct sockaddr*)&listener_sin, sizeof(listener_sin));
	// if (!listener) {
	// 	log_error("Couldn't create listener");
	// 	exit(1);
	// }
	// event_base_dispatch(base);
	// evconnlistener_free(listener);
	// event_base_free(base);
}