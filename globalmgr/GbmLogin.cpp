
#include "GbmLogin.hpp"


GbmLogin::GbmLogin()
{
}


GbmLogin::~GbmLogin()
{
	std::cout << "GbmLogin destory" << std::endl;
}

void GbmLogin::Init()
{
	std::cout << "GbmLogin Init." << std::endl;
}

void GbmLogin::CallBack(std::string msg)
{
	std::cout << "GbmLogin CallBack." << std::endl;
	SendMsg(DB_TASK, "I am GbmLogin.");
}
