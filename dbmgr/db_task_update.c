#include "servant_def.h"
#include "log.h"
#include "db_ops.h"

#include <stdio.h>
#include <string.h>

void *db_task_update(struct servant_context *ctx)
{
	log_debug("db_task_update receive: strlen(%d) sizeof(%d) msg(%s)", 
		strlen(ctx->servant_param), sizeof(*ctx->servant_param), ctx->servant_param);

	db_ops("update test set count=count*2");
	return NULL;
}