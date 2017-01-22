#pragma once

#include "ServantBase.hpp"

class GsLogin:public ServantBase
{
public:
	GsLogin();
	virtual ~GsLogin();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

