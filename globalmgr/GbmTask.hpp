#pragma once
#include "ServantBase.hpp"

class GbmTask:public ServantBase
{
public:
	GbmTask();
	virtual ~GbmTask();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

