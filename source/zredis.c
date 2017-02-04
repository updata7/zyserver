#include "zredis.h"
#include "log.h"

#include <string.h>

redisContext *pRedisContext = NULL;

void redis_connect(const char *host, const int port, struct timeval timeout)
{
	pRedisContext = (redisContext*)redisConnectWithTimeout(host, port, timeout);
	if ( (NULL == pRedisContext) || (pRedisContext->err) )
	{
		if (pRedisContext)
		{
			log_error("connect error: %s", pRedisContext->errstr);
		} else {
			log_error("connect error: can't allocate redis context.");
		}

		return;
	}

	log_info("zredis:redis_connect success.");

	char ret_str[1024] = {0};
	redis_commond(ret_str, "set %s %s", "k1", "v1");
	memset(ret_str, 0, 1024);
	redis_commond(ret_str, "get %s", "k1");
}

void redis_commond(char *ret_str, const char *fmt, ...)
{
	if (NULL == pRedisContext) {
		log_error("zredis:redis_commond pRedisContext is NULL");
		return;
	}

	redisReply *reply;
	va_list ap;
	va_start(ap, fmt);
	// TODO
	reply = (redisReply *)redisCommand(pRedisContext, fmt, ap);
	va_end(ap);
	strcpy(ret_str, reply->str);
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