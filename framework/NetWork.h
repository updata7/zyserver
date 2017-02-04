#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "server_config.h"
#include "net_work.h"

#include <event2/event.h>
#include <event2/thread.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event_compat.h>
#include <event2/event_struct.h>

#include <list>

#define MAX_SERVER 5

class NetWork
{
public:
	NetWork(struct server_config_t *sc);
	~NetWork();
	void Start();
	static void SendMsg(SERVANT_TYPE servant, const char *msg);
	void RegServerConnectedCb(net_work_callback cb, void *userdata);
	void RegServerClosedCb(net_work_callback cb, void *userdata);
	void RegClientInCb(net_work_callback cb, void *userdata);
	void RegClientOutCb(net_work_callback cb, void *userdata);
private:
	struct server_config_t *server_config;
	static void OnClientClose(socket_t fd, void *userdata);
	// static void OnServerConnected(socket_t fd, void *userdata);
	// static void listener_cb(struct evconnlistener* listener, int fd, struct sockaddr* sa, int socklen, void* user_data);
	// static void read_cb(struct bufferevent *bev, void *userdata);
	// static void connect_eventcb(struct bufferevent *bev, short events, void *userdata);
	// static void event_cb(struct bufferevent *bev, short events, void *userdata);
	// void ConnectServer();
};

#endif 	// NETWORK_HPP