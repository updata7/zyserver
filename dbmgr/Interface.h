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
	void OneClientOut(socket_t fd);
private:
	ServantHandler *sh;
	void RegisterTimer(timer_execute_func func, void *userdata, int msec);
};

#endif 	// INTERFACE_H