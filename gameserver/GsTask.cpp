
#include "GsTask.h"


GsTask::GsTask()
{
}


GsTask::~GsTask()
{
	std::cout << "GsTask destory" << std::endl;
}

void GsTask::Init()
{
	std::cout << "GsTask Init." << std::endl;
}

void GsTask::CallBack(std::string msg)
{
	std::cout << "GsTask CallBack." << std::endl;
	SendMsg(DB_TASK, "I am GsTask.");
}
