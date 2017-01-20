#include "server_thread.h"
#include "log.h"

#include <stdlib.h>

void create_thread(pthread_t *thread, void *(*start_routine) (void *), void *arg)
{
	int errcode = pthread_create(thread, NULL, start_routine, arg);
	if (errcode != 0) {
		log_error("create_thread failed, errcode(%d)", errcode);
		exit(1);
	}
}

void exit_thread()
{
	pthread_exit(NULL);
}
