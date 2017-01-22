#pragma once

#include "ServantBase.hpp"

class GbmLogin:public ServantBase
{
public:
	GbmLogin();
	virtual ~GbmLogin();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

