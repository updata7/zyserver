#include "Interface.hpp"
#include "GbmTask.hpp"
#include "GbmLogin.hpp"

#include <iostream>

Interface::Interface(ServantHandler *Sh)
{
	sh = Sh;
}


Interface::~Interface()
{
}

void Interface::OneClientOut(socket_t fd)
{
	log_debug("client fd %d out", fd);
}

// 注册定时器，单位毫秒
void Interface::RegisterTimer(timer_execute_func func, void *userdata, int msec)
{
	timer_register(func, userdata, msec);
}

static void test_timer(void *userdata)
{
	// log_debug("test_timer %d %d", 9, 9);
}

void Interface::Start()
{
	RegisterHandler(GBM_LOGIN, sh, GbmLogin);
	RegisterHandler(GBM_TASK, sh, GbmTask);

	RegisterTimer(test_timer, NULL, 1000);
}