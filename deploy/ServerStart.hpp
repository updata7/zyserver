#ifndef SERVERSTART_H
#define SERVERSTART_H

#include "server_config.h"

class ServerStart
{
public:
	ServerStart(struct server_config_t *sc);
	void Start();
private:
	struct server_config_t *server_config;
};

#endif	// SERVERSTART_H