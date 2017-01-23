#include "DbLogin.hpp"
#include "db_ops.h"

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
	db_ops("insert into test(count) value(17);");
	db_get_data();

	SendMsg(GS_TASK, "I am DbLogin.");
}
