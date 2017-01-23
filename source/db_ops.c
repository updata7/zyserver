#include "db_ops.h"
#include "log.h"

#include <mysql/mysql.h>
#include <mysql/errmsg.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define MAX_COLUMN_LEN    32
#define zy_evutil_vsnprintf vsnprintf

MYSQL mysql;

static int db_connected = 0;

static bool db_check_connect()
{
	if (db_connected) {
		return true;
	}

	log_error("mysql not init yet, maybe it is not the dbserver");
	return false;
}

void db_connect(const char *db_host, const char *db_user, const char *db_pwd,
	const char *database, const int db_post)
{
	if (NULL == mysql_init(&mysql)) {    //分配和初始化MYSQL对象  
        log_error("mysql_init failed: error(%s)", mysql_error(&mysql));  
        exit(1);  
    }
	
	if (NULL == mysql_real_connect(&mysql,  
                db_host,  
                db_user,  
                db_pwd,  
                database,  
                db_post,  
                NULL,  
                0)) {
        log_error("mysql_real_connect(): %s", mysql_error(&mysql));  
        exit(1);
    }

    db_connected = 1;
}

void db_close(void)
{
	if (!db_check_connect()) {
		return;
	}
	mysql_close(&mysql);
}

void db_query()
{
	if (!db_check_connect()) {
		return;
	}

	const char *create_tab_str = " 	\
		DROP TABLE IF EXISTS `test`; 	\
		CREATE TABLE `test` ( 	\
		  `id` smallint(8) unsigned NOT NULL AUTO_INCREMENT, 	\
		  `count` bigint(20) NOT NULL DEFAULT 99, 	\
		  PRIMARY KEY (`id`), 	\
		  KEY `count` (`count`) USING BTREE 	\
		) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='测试表';";
	
	mysql_real_query(&mysql, create_tab_str, strlen(create_tab_str));
}

int db_ops(char *fmt, ...)
{
	if (!db_check_connect()) {
		return -1;
	}
	char sql[1024] = {0};
	int rc;
	va_list ap;
	va_start(ap, fmt);
	zy_evutil_vsnprintf(sql, sizeof(sql), fmt, ap);
	va_end(ap);
	if ((rc = mysql_real_query(&mysql, sql, strlen(sql))) != 0) {
		log_error("db_ops: mysql_real_query failed, error(%s)", mysql_error(&mysql));
		return -1;
	}

	return 0;
}

static int get_num_rows(MYSQL_RES *res)
{
	if (!db_check_connect()) {
		return -1;
	}
	return mysql_num_rows(res);
}

int db_get_data()
{
	if (!db_check_connect()) {
		return -1;
	}
	MYSQL_RES *result;
	MYSQL_FIELD *fd;
	MYSQL_ROW sql_row;
	result = mysql_store_result(&mysql);
	if (!result) {
		return 1;
	}

	char column[MAX_COLUMN_LEN][MAX_COLUMN_LEN];
	log_info("the result number is %d", get_num_rows(result));
	int i = 0, j;

	// 获取列名
	while (NULL != (fd = mysql_fetch_field(result))) {
		bzero(column[i], sizeof(column[i]));
		strcpy(column[i], fd->name);
		++ i;
	}

	j = mysql_num_fields(result);
    for (i = 0; i < j; i++) {
        printf("%s\t",column[i]);
    }
    printf("\n");

    //获取具体的数据
    while (NULL != (sql_row = mysql_fetch_row(result))) {
        for (i = 0; i < j; i++) {
            printf("%s\t", sql_row[i]);
        }
        printf("\n");
    }

    return 0;
}