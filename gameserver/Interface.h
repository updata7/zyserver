#ifndef INTERFACE_H
#define INTERFACE_H

#ifndef socket_t
#define socket_t int
#endif 	// socket_t

#include "ServantHandler.h"
#include "timer.h"

class Interface
{
public:
	Interface(ServantHandler *Sh);
	~Interface();
	void Start();
	void OneClientOut(socket_t fd);
private:
	ServantHandler *sh;
	void RegisterTimer(timer_execute_func func, void *userdata, int msec);
};

#endif 	// INTERFACE_H