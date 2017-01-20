#ifndef SERVER_ENV_H
#define SERVER_ENV_H

#ifdef __cplusplus
extern "C" {
#endif 	// __cplusplus

struct server_env;

void env_init(const char *machine_conf, const char *config);
char * get_env_value(char *key, char *def_value);

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif // SERVER_ENV_H