#ifndef SERVER_IMP_H
#define SERVER_IMP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct server_config_t {
	const char *address;
	int port;
	int prefix;
	const char *logpath;
	const char *endpointlist;
	int thread;
	int dbenable;
};

struct db_config_t {
	const char *dbhost;
	int dbport;
	const char *dbname;
	const char *dbuser;
	const char *dbpwd;
};

struct server_config_t * get_server_config();
void init_server_config(const char *address, int port, int prefix, 
	const char *logpath, const char *endpointlist, int thread, int dbenable);
void init_db_config(const char *dbhost,	int dbport,	const char *dbname,	const char *dbuser,	const char *dbpwd);
struct db_config_t *get_db_config();

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif 	// SERVER_IMP_H