#pragma once
#include "ServantBase.h"

class GsTask:public ServantBase
{
public:
	GsTask();
	virtual ~GsTask();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

