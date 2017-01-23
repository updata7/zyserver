#include "DbTask.h"

DbTask::DbTask()
{
}


DbTask::~DbTask()
{
	std::cout << "DbTask destory" << std::endl;
}

void DbTask::Init()
{
	std::cout << "DbTask Init." << std::endl;
}

void DbTask::CallBack(std::string msg)
{
	std::cout << "DbTask CallBack." << std::endl;
}
