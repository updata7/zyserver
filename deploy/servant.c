#include "servant.h"
#include "malloc.h"
#include "log.h"

#include <assert.h>
#include <string.h>

struct servant_t {
	servant_cb cb;
	void *userdata;
};
static bool servant_init = false; 	// 注册完回调之后则认为初始化成功
static struct servant_t S;

void servant_reg_callback(servant_cb cb, void *userdata)
{
	S.cb = cb;
	S.userdata = userdata;
	servant_init = true;
}

void servant_dispatch(struct message_queue *mq)
{
	if (!servant_init) return;

	char *msg = mq->msg;
	int len = mq->len;
	SERVANT_TYPE servant;
	char h[SERVANT_SIZE+1] = {0};
	char *message = (char *)Malloc(len - SERVANT_SIZE + 1);
	memset(message, 0, len - SERVANT_SIZE + 1);

	strncpy(h, msg, SERVANT_SIZE);
	servant = strtol(h, NULL, 16);

	strncpy(message, msg + SERVANT_SIZE, len - SERVANT_SIZE);
	log_debug("servant(%s) message(%s)\n", h, message);
	S.cb(S.userdata, servant, message);
	Free(message);
}