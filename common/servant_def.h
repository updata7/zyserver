#ifndef _SERVANT_DEF_H_
#define _SERVANT_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif 	// __cplusplus

#include "servant.h"

// gamesv 前缀 0x0001
#define GV_TASK 0x00010001
#define GV_TASK_SELECT 0x00010002

// dbmgr 前缀 0x0002
#define DB_TASK_INSERT 0x00020001
#define DB_TASK_UPDATE 0x00020002
#define DB_TASK_SELECT 0x00020003

struct servant_t * reg_servant();
void reg_timer();

void *gv_task(struct servant_context *);
void *gv_task_select(struct servant_context *);

void *db_task_insert(struct servant_context *);
void *db_task_update(struct servant_context *);
void *db_task_select(struct servant_context *);


void test_timer(void);
void test_timer2(void);
void test_timer3(void);
void test_timer4(void);

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif 	// _SERVANT_DEF_H_