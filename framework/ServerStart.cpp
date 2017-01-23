#include "ServerStart.h"
#include "server_config.h"
#include "NetWork.h"
#include "timer.h"
#include "MessageDispatch.h"
#include "malloc.h"
#include "TimerMgr.h"
#include "ServantHandler.h"
#include "Interface.h" 
#include "db_ops.h"

#include <iostream>

using namespace std;

// extern struct server_config_t server_config;

ServerStart::ServerStart(struct server_config_t *sc)
{
	server_config = sc;
	db_config = NULL;
}

ServerStart::ServerStart(struct server_config_t *sc, struct db_config_t *db)
{
	server_config = sc;
	db_config = db;
	db_connect(db_config->dbhost, db_config->dbuser, db_config->dbpwd, db_config->dbname, db_config->dbport);
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