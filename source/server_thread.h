#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#ifdef __cplusplus
extern "C" {
#endif 	// __cplusplus

#include <pthread.h>

void create_thread(pthread_t *thread, void *(*start_routine) (void *), void *arg);
void exit_thread();

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif 	// SERVER_THREAD_H