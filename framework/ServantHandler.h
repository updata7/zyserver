#ifndef SERVANTHANDLER_H
#define SERVANTHANDLER_H

#include <map>
#include "ServantBase.h"
#include "servant.h"
#include "malloc.h"
#include "log.h"

#ifndef SERVANT_TYPE 
#define SERVANT_TYPE long
#endif 	// SERVANT_TYPE

#define RegisterHandler(servant, servantHandler, servantClass)	\
	ServantBase *servantClass##_sb = NEW servantClass();	\
	servantHandler->AddHandler(servant, servantClass##_sb);
	
class ServantHandler
{
public:
	ServantHandler();
	virtual ~ServantHandler();

	void AddHandler(SERVANT_TYPE servant, ServantBase *callback);
	void ExecuteHandler(SERVANT_TYPE servant);
	void LoadHandler();
	bool RunHandlerByServant(SERVANT_TYPE servant, std::string msg);
	void ReleaseHandler();
private:
	typedef std::map<SERVANT_TYPE, ServantBase*> ServantMap;
	ServantMap servantMap;
	static void ServantCallBack(void *userdata, SERVANT_TYPE servant, char *msg);
};

#endif 	// SERVANTHANDLER_H