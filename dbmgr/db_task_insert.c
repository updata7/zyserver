#include "servant_def.h"
#include "log.h"
#include "db_ops.h"

#include <stdio.h>
#include <string.h>

void *db_task_insert(struct servant_context *ctx)
{
	log_debug("db_task_insert receive: strlen(%d) sizeof(%d) msg(%s)", 
		strlen(ctx->servant_param), sizeof(*ctx->servant_param), ctx->servant_param);

	db_ops("insert into test(count) value(\"%d\")", 7);
	return NULL;
}