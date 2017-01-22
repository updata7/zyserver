#pragma once

#include "ServantBase.hpp"

class Servant2:public ServantBase
{
public:
	Servant2();
	virtual ~Servant2();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

