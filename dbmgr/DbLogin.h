#pragma once

#include "ServantBase.h"

class DbLogin:public ServantBase
{
public:
	DbLogin();
	virtual ~DbLogin();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

