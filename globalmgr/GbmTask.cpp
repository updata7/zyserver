#include "GbmTask.h"


GbmTask::GbmTask()
{
}


GbmTask::~GbmTask()
{
	std::cout << "GbmTask destory" << std::endl;
}

void GbmTask::Init()
{
	std::cout << "GbmTask Init." << std::endl;
}

void GbmTask::CallBack(std::string msg)
{
	std::cout << "GbmTask CallBack." << std::endl;
}
