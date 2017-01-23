#include "Interface.h"
#include "GbmTask.h"
#include "GbmLogin.h"

#include <iostream>

Interface::Interface(ServantHandler *Sh)
{
	sh = Sh;
}


Interface::~Interface()
{
}

// 注册定时器，单位毫秒
void Interface::RegisterTimer(timer_execute_func func, void *userdata, int msec)
{
	timer_register(func, userdata, msec);
}

void Interface::OnServerConnected(socket_t fd, void *userdata)
{
	// Interface *ie = (Interface *)userdata;
	std::cout << "Interface:OnServerConnected fd = " << fd << std::endl;
}

void Interface::OnServerClosed(socket_t fd, void *userdata)
{
	// Interface *ie = (Interface *)userdata;
	std::cout << "Interface:OnServerClosed fd = " << fd << std::endl;
}

void Interface::OnClientIn(socket_t fd, void *userdata)
{
	// Interface *ie = (Interface *)userdata;
	std::cout << "Interface:OnClientIn fd = " << fd << std::endl;
}

void Interface::OnClientOut(socket_t fd, void *userdata)
{
	// Interface *ie = (Interface *)userdata;
	std::cout << "Interface:OnClientOut fd = " << fd << std::endl;
}

// 定时器函数例子1
static void timer_example(void *userdata)
{
	// log_debug("test_timer %d %d", 9, 9);
}

// 定时器函数例子2 注意要是static,public或者private均可
void Interface::timer_example2(void *userdata)
{

}

void Interface::Start()
{
	RegisterHandler(GBM_LOGIN, sh, GbmLogin);
	RegisterHandler(GBM_TASK, sh, GbmTask);

	RegisterTimer(timer_example, NULL, 1000);
	RegisterTimer(timer_example2, NULL, 1000);
}