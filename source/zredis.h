#ifndef ZREDIS_H
#define ZREDIS_H

#include <hiredis/hiredis.h>
#include <sys/time.h>
#include <stdarg.h>

void redis_connect(const char *host, const int port, struct timeval timeout);
void redis_commond(char *ret_str, const char *fmt, ...);
void redis_free();

#endif 	// ZREDIS_H