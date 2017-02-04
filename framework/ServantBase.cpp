
#include "ServantBase.h"
#include "NetWork.h"
#include "log.h"

ServantBase::ServantBase()
{
}


ServantBase::~ServantBase()
{
}

void ServantBase::Init()
{
	std::cout << "ServantBase Init" << std::endl;
}

void ServantBase::Encode(void *protocol)
{
}

void ServantBase::Decode(void *protocol)
{
}

void ServantBase::CallBack(std::string class_data)
{
	std::cout << "ServantBase CallBack" << std::endl;
}

void ServantBase::SendMsg(SERVANT_TYPE servant, const char *msg)
{
	log_debug("ServantBase:SendMsg(%s) to servant(0x%08X)", msg, servant);
	NetWork::SendMsg(servant, msg);
}