#ifndef THREADMUTEX_H
#define THREADMUTEX_H

#include "server_thread.h"
#include "log.h"

#include <iostream>

class ThreadMutex
{
public:
	pthread_mutex_t mutex;
	ThreadMutex()
	{
		if (pthread_mutex_init(&mutex, NULL)) {
			log_error("Init mutex error");
			exit(1);
		}
	}

	~ThreadMutex()
	{
		pthread_mutex_destroy(&mutex);
	}
};
#endif 	// THREADMUTEX_H