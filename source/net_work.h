#ifndef NETWROK_H
#define NETWROK_H

#ifdef __cplusplus
extern "C" {
#endif 	// __cplusplus

#include "server_config.h"
#include <event2/event.h>
#include <event2/thread.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event_compat.h>
#include <event2/event_struct.h>

#include "util.h"

#ifndef socket_t
#define socket_t int
#endif 	// socket_t
	
typedef void (*net_work_callback)(socket_t, void *);

void read_helper(struct bufferevent *bev);
void read_cb(struct bufferevent *bev, void *userdata);
// static void event_cb(struct bufferevent *bev, short events, void *ctx);
void accepted_cb(struct evconnlistener *listener, socket_t fd,
	struct sockaddr *address, int socklen, void *userdata);
void net_work_init();
void *run_thread(void *userdata);
// static void connect_eventcb(struct bufferevent *bev, short events, void *userdata);
void net_work_connect(const char *endpointlist);
void net_work_run(const char *address, int port, const char *endpointlist, int prefix);
int get_client_conn();
int get_server_conn();

void net_work_reg_onclientclose(net_work_callback onclientclose_cb, void *userdata); 		// 某个客户端断线的回调
void net_work_reg_onserverconnected(net_work_callback onserverconnected_cb, void *userdata); 	// 连接上某个服务器的回调
void send_msg(SERVANT_TYPE servant, const char *msg, int size);

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif 	// NETWROK_H