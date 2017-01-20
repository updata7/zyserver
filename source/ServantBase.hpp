#ifndef SERVANTBASE_H
#define SERVANTBASE_H

#include <iostream>
class ServantBase
{
public:
	ServantBase();
	virtual ~ServantBase();
	virtual void CallBack(std::string msg);
	virtual void Init();
};

#endif 	// SERVANTBASE_H