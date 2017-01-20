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

struct server_config_t * get_server_config();
void init_server_config(const char *address, int port, int prefix, 
	const char *logpath, const char *endpointlist, int thread, int dbenable);

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif 	// SERVER_IMP_H