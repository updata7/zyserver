#ifndef SERVANTDEF_H
#define SERVANTDEF_H

// for gameserver 0x0001 prefix
#define GS_PREFIX 0x0001
#define GS_LOGIN 0x00010001 	// 登录
#define GS_TASK  0x00010002		// 任务

// for dbmgr 0x0002 prefix
#define DB_PREFIX 0x0002
#define DB_LOGIN 0x00020001
#define DB_TASK 0x00020002

// for globalmgr 0x0003 prefix
#define GBM_PREFIX 0x0003
#define GBM_LOGIN 0x00030001
#define GBM_TASK 0x00030002

#endif 	// SERVANTDEF_H