
#include "DbLogin.hpp"


DbLogin::DbLogin()
{
}


DbLogin::~DbLogin()
{
	std::cout << "DbLogin destory" << std::endl;
}

void DbLogin::Init()
{
	std::cout << "DbLogin Init." << std::endl;
}

void DbLogin::CallBack(std::string msg)
{
	std::cout << "DbLogin CallBack." << std::endl;
	SendMsg(GS_TASK, "I am DbLogin.");
}
