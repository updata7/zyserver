#pragma once
#include "ServantBase.hpp"

class Servant1:public ServantBase
{
public:
	Servant1();
	virtual ~Servant1();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

