#ifndef INTERFACE_H
#define INTERFACE_H

#include "ServantHandler.h"
#include "log.h"
#include "timer.h"
#include "macro.h"

class Interface
{
public:
	Interface(ServantHandler *Sh);
	~Interface();
	void Start();
	static void OnServerConnected(socket_t fd, void *userdata);
	static void OnServerClosed(socket_t fd, void *userdata);
	static void OnClientIn(socket_t fd, void *userdata);
	static void OnClientOut(socket_t fd, void *userdata);
private:
	ServantHandler *sh;
	void RegisterTimer(timer_execute_func func, void *userdata, int msec);
	static void timer_example2(void *userdata);
};

#endif 	// INTERFACE_H