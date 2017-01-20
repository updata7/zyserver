#include "mq.h"
#include "malloc.h"
#include "servant.h"
#include "util.h"
#include "log.h"

#include <assert.h>
#include <string.h>

struct global_queue *Q = NULL;

static struct message_queue * mq_create(struct bufferevent *bev, char *msg)
{
	struct message_queue *mq = (struct message_queue *)Malloc(sizeof(*mq));
	mq->bev = bev;
	mq->len = strlen(msg);
	mq->msg = msg;

	mq->next = NULL;
	SPIN_INIT(mq);
	return mq;
}

void global_mq_init()
{
	struct global_queue *q = (struct global_queue *)Malloc(sizeof(*q));
	memset(q, 0, sizeof(*q));
	SPIN_INIT(q);
	Q=q;
}

void mq_push(struct bufferevent *bev, char *msg)
{
	struct message_queue *mq = mq_create(bev, msg);

	struct global_queue *q = Q;
	SPIN_LOCK(q)
	if(q->tail) {
		q->tail->next = mq;
		q->tail = mq;
	} else {
		q->head = q->tail = mq;
	}
	SPIN_UNLOCK(q)
}

void mq_dispatch() 
{
	struct message_queue *mq = mq_pop();
	if (mq == NULL) {
		return;
	}

	log_debug("message came %s", mq->msg);

	servant_dispatch(mq);
	mq_release(mq);
}

struct message_queue *mq_pop()
{
	struct global_queue *q = Q;
	SPIN_LOCK(q)

	struct message_queue *mq = q->head;
	if(mq) {
		q->head = mq->next;
		if(q->head == NULL) {
			assert(mq == q->tail);
			q->tail = NULL;
		}
		mq->next = NULL;
	}

	SPIN_UNLOCK(q)

	return mq;
}

void mq_release(struct message_queue *mq)
{
	SPIN_DESTROY(mq);
	Free(mq->msg);
	Free(mq);
}