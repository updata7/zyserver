#include "ServerStart.hpp"
#include "server_config.h"
#include "ThreadMutex.hpp"
#include "NetWork.hpp"
#include "timer.h"
#include "MessageDispatch.hpp"
#include "Memory.hpp"
#include "TimerMgr.hpp"
#include "ServantHandler.hpp"
#include "Interface.hpp" 

#include <iostream>

using namespace std;

// extern struct server_config_t server_config;

ServerStart::ServerStart(struct server_config_t *sc)
{
	server_config = sc;
}

void ServerStart::Start()
{
	NetWork *nt = NEW NetWork(server_config);
	nt->Start();

	TimerMgr *tm = NEW TimerMgr();

	ServantHandler *sh = NEW ServantHandler();
	Interface *ie = NEW Interface(sh);
	ie->Start();
	sh->LoadHandler();

	tm->Start();

	MessageDispatch *md = NEW MessageDispatch();
	md->Start();

	// sh->RunHandlerByServant("2", "test");

	sh->ReleaseHandler();
	DELETE ie;
	DELETE sh;

	DELETE nt;
	DELETE md;
	DELETE tm;
}