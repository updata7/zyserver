#pragma once
#include "ServantBase.hpp"

class DbTask:public ServantBase
{
public:
	DbTask();
	virtual ~DbTask();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

