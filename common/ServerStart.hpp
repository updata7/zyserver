#ifndef SERVERSTART_H
#define SERVERSTART_H

#include "server_config.h"

class ServerStart
{
public:
	ServerStart(struct server_config_t *sc);
	ServerStart(struct server_config_t *sc, struct db_config_t *db);
	void Start();
private:
	struct server_config_t *server_config;
	struct db_config_t *db_config;
};

#endif	// SERVERSTART_H