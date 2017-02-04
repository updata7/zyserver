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
	NetWork *nw = NEW NetWork(server_config);

	TimerMgr *timer_mgr = NEW TimerMgr();
	ServantHandler *servant_handler = NEW ServantHandler();
	Interface *inter_face = NEW Interface(servant_handler);

	nw->RegServerConnectedCb(inter_face->OnServerConnected, inter_face);
	nw->RegServerClosedCb(inter_face->OnServerClosed, inter_face);
	nw->RegClientInCb(inter_face->OnClientIn, inter_face);
	nw->RegClientOutCb(inter_face->OnClientOut, inter_face);
	nw->Start();
	
	inter_face->Start();
	servant_handler->LoadHandler();

	MessageDispatch *msg_dispatch = NEW MessageDispatch();

	timer_mgr->Start();
	msg_dispatch->Start();

	servant_handler->ReleaseHandler();
	DELETE inter_face;
	DELETE servant_handler;

	DELETE nw;
	DELETE msg_dispatch;
	DELETE timer_mgr;
}