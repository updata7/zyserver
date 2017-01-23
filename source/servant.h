#ifndef _SERVANT_H_
#define _SERVANT_H_

#ifdef __cplusplus
extern "C" {
#endif 	// __cplusplus

#include "mq.h"
#include "macro.h"

typedef void (*servant_cb)(void *userdata, SERVANT_TYPE servant, char *msg);

void servant_dispatch(struct message_queue *mq);

void servant_reg_callback(servant_cb cb, void *userdata);

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif 	// _SERVANT_H_