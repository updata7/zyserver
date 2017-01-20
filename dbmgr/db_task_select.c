#include "interface.h"
#include "servant_def.h"
#include "log.h"
#include "db_ops.h"

#include <stdio.h>
#include <string.h>

void *db_task_select(struct servant_context *ctx)
{
	log_debug("db_task_select receive: strlen(%d) msg(%s)", 
		strlen(ctx->servant_param), ctx->servant_param);

	db_ops("select * from test");
	get_data();
	// call(GV_TASK_SELECT, "task select success.");
	return NULL;
}