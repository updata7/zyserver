#include "ServantHandler.h"

ServantHandler::ServantHandler()
{
}


ServantHandler::~ServantHandler()
{
}

void ServantHandler::AddHandler(SERVANT_TYPE servant, ServantBase *servantClass)
{
	servantMap.insert(ServantMap::value_type(servant, servantClass));
}

void ServantHandler::ServantCallBack(void *userdata, SERVANT_TYPE servant, char *msg)
{
	ServantHandler *sh = (ServantHandler *)userdata;
	if (!sh->RunHandlerByServant(servant, msg)) {
		log_error("found no servant(0x%08X)", servant);
	}
}

void ServantHandler::LoadHandler()
{
	ServantMap::iterator it = servantMap.begin();
	for (; it != servantMap.end(); it++)
	{
		it->second->Init();
	}

	servant_reg_callback(ServantCallBack, this);
}

bool ServantHandler::RunHandlerByServant(SERVANT_TYPE servant, std::string msg)
{
	ServantMap::iterator it = servantMap.find(servant);
	if (it != servantMap.end())
	{
		it->second->CallBack(msg);
		return true;
	}

	return false;
}

void ServantHandler::ReleaseHandler()
{
	ServantMap::iterator it = servantMap.begin();
	for (; it != servantMap.end(); it++)
	{
		DELETE it->second;
	}
}