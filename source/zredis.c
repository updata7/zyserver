#include "zredis.h"
#include "log.h"

#include <string.h>
#include <stdlib.h>

#define REDIS_CMD_LEN 1024

redisContext *pRedisContext = NULL;
	
void redis_connect(const char *host, const int port, struct timeval timeout)
{
	pRedisContext = (redisContext*)redisConnectWithTimeout(host, port, timeout);
	if ( (NULL == pRedisContext) || (pRedisContext->err) )
	{
		if (pRedisContext)
		{
			log_error("redis connect error: %s", pRedisContext->errstr);
		} else {
			log_error("redis connect error: can't allocate redis context.");
		}

		exit(1);
	}

	log_info("zredis:redis_connect success.");

	// char ret_str[1024] = {0};
	// redis_commond(ret_str, "set1 %s %s", "k1", "v1");
	// memset(ret_str, 0, 1024);
	// redis_commond(ret_str, "get %s", "k2");
}

void redis_commond(char *ret_str, const char *fmt, ...)
{
	if (NULL == pRedisContext) {
		log_error("zredis:redis_commond pRedisContext is NULL");
		return;
	}

	char cmd_str[REDIS_CMD_LEN] = {0};

	redisReply *reply;
	va_list ap;
	va_start(ap, fmt);
	zy_evutil_vsnprintf(cmd_str, sizeof(cmd_str), fmt, ap);
	reply = (redisReply *)redisCommand(pRedisContext, cmd_str);
	va_end(ap);
	if (NULL != reply && reply->str) {
		strcpy(ret_str, reply->str);
	}

	freeReplyObject(reply);
}

void redis_free()
{
	if (NULL == pRedisContext) {
		log_error("zredis:redis_free pRedisContext is NULL");
		return;
	}
	redisFree(pRedisContext);
}