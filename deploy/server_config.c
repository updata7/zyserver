#include "server_config.h"

static server_config_t server_config;

void init_server_config(const char *address, int port, int prefix, const char *logpath, const char *endpointlist, int thread, int dbenable)
{
	server_config.address = address;
	server_config.port = port;
	server_config.prefix = prefix;
	server_config.logpath = logpath;
	server_config.endpointlist = endpointlist;
	server_config.thread = thread;
	server_config.dbenable = dbenable;
}

struct server_config_t * get_server_config()
{
	return &server_config;
}