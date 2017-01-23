#ifndef SERVANTBASE_H
#define SERVANTBASE_H

#include "ServantDef.hpp"

#include <iostream>

class ServantBase
{
public:
	ServantBase();
	virtual ~ServantBase();
	virtual void CallBack(std::string msg);
	virtual void Init();
	
	virtual void Encode(void *protocol); 	// 封包
	virtual void Decode(void *protocol); 	// 解包

	void SendMsg(SERVANT_TYPE servant, const char *msg);
};

#endif 	// SERVANTBASE_H