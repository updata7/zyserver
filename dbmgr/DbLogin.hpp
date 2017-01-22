#pragma once

#include "ServantBase.hpp"

class DbLogin:public ServantBase
{
public:
	DbLogin();
	virtual ~DbLogin();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

