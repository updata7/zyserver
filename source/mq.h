#ifndef MQ_H
#define MQ_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <event2/bufferevent.h>
#include "spinlock.h"

struct message_queue {
	struct spinlock lock;
	struct bufferevent *bev;
	int len;
	char *msg;
	struct message_queue *next;
};

struct global_queue {
	struct message_queue *head;
	struct message_queue *tail;
	struct spinlock lock;
};

// struct message_queue * mq_create(socket_t session);
void global_mq_init();
void mq_push(struct bufferevent *bev, char *);
struct message_queue *mq_pop();
void mq_release(struct message_queue *);
void mq_dispatch();

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif 	// MQ_H