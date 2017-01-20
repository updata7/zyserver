#include "Interface.hpp"
#include "Servant1.hpp"
#include "Servant2.hpp"

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
	log_debug("test_timer %d %d", 9, 9);
}

void Interface::Start()
{
	RegisterHandler(0x00010001, sh, Servant1);
	RegisterHandler(0x00020001, sh, Servant2);

	RegisterTimer(test_timer, NULL, 1000);
}