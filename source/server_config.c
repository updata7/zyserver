#include "server_config.h"

static server_config_t server_config;
static struct db_config_t db_config;

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

void init_db_config(const char *dbhost,	int dbport,	const char *dbname,	const char *dbuser,	const char *dbpwd)
{
	db_config.dbhost = dbhost;
	db_config.dbport = dbport;
	db_config.dbname = dbname;
	db_config.dbuser = dbuser;
	db_config.dbpwd = dbpwd;
}

struct db_config_t *get_db_config()
{
	return &db_config;
}