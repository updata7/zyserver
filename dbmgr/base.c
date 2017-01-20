#include "servant_def.h"
#include "timer.h"

struct servant_t * reg_servant()
{
	static struct servant_t s[] = {
		{DB_TASK_INSERT, db_task_insert},
		{DB_TASK_UPDATE, db_task_update},
		{DB_TASK_SELECT, db_task_select},
		{0, NULL},
	};

	return s;
}

void reg_timer()
{
	// timer_register(test_timer, 1*1000);
	// timer_register(test_timer2, 2*1000);
	// timer_register(test_timer3, 3*1000);
	// timer_register(test_timer4, 4*1000);
}

