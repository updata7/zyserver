#include "MessageDispatch.hpp"
#include "mq.h"

MessageDispatch::MessageDispatch()
{
	global_mq_init();	
}

MessageDispatch::~MessageDispatch()
{
}

void MessageDispatch::DispatchMessage(void *userdata)
{
}

void MessageDispatch::Start()
{
	while(1) {
		mq_dispatch();
	}
}