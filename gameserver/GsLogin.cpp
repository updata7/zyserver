
#include "GsLogin.hpp"


GsLogin::GsLogin()
{
}


GsLogin::~GsLogin()
{
	std::cout << "GsLogin destory" << std::endl;
}

void GsLogin::Init()
{
	std::cout << "GsLogin Init." << std::endl;
}

void GsLogin::CallBack(std::string msg)
{
	std::cout << "GsLogin CallBack." << std::endl;
	SendMsg(DB_LOGIN, "I am GsLogin.");
}
