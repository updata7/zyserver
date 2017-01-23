#ifndef _DB_OPS_H_
#define _DB_OPS_H_

#ifdef __cplusplus
extern "C" {
#endif 	// __cplusplus

void db_connect(const char *host_name, const char *user_name, const char *password,
	const char *database, const int port);
void db_close(void);
int db_ops(char *fmt, ...);
int db_get_data();
void db_query();
#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif 	// _DB_OPS_H_