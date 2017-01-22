#pragma once
#include "ServantBase.hpp"

class GsTask:public ServantBase
{
public:
	GsTask();
	virtual ~GsTask();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

