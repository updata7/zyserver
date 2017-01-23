#include "TimerMgr.hpp"
#include "server_thread.h"
#include "timer.h"

TimerMgr::TimerMgr()
{
	timer_init();
}

TimerMgr::~TimerMgr()
{
	timer_release();	
}

void *TimerMgr::Execute(void *userdata)
{
	for (;;) {
		timer_update();
	}

	return NULL;
}

void TimerMgr::Start()
{
	pthread_t t_id;
	create_thread(&t_id, Execute, this);
}