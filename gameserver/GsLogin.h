#pragma once

#include "ServantBase.h"

class GsLogin:public ServantBase
{
public:
	GsLogin();
	virtual ~GsLogin();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

