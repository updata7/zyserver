#include "log.h"
#include "spinlock.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/time.h>

#define LOG_MESSAGE_SIZE 4096
#define LOG_DATE_SIZE 24

struct log_t {
	const char *logpath;
	FILE *log_fp;
	struct spinlock lock;
};

typedef enum log_level_e {
	LOG_ERROR,
	LOG_WARN,
	LOG_INFO,
	LOG_DEBUG,
}LOG_LEVEL;

static struct log_t LOG;

static void _get_date_buf(char *buf)
{
	time_t timep;
	time(&timep);
	struct tm *p = localtime(&timep);
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int msec = tv.tv_usec / 1000;	// 毫秒

	sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d.%03d", 
		1900 + p->tm_year, p->tm_mon+1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, msec);
}

static void _log(LOG_LEVEL log_level, const char *log_msg)
{
	char buf[LOG_DATE_SIZE] = {0};
	char total_buf[LOG_MESSAGE_SIZE+LOG_DATE_SIZE] = {0};
	_get_date_buf(buf);

	FILE *fout;
	char *log_levelp = NULL;

	switch(log_level) {
	case LOG_ERROR:
		log_levelp = "[ERROR]";
		fout = stderr;
		break;
	case LOG_WARN:
		log_levelp = "[WARN]";
		fout = stderr;
		break;
	case LOG_INFO:
		log_levelp = "[INFO]";
		fout = stdout;
		break;
	case LOG_DEBUG:
		log_levelp = "[DEBUG]";
		fout = stdout;
		break;
	default:
		log_levelp = "[UNKONW]";
		fout = stderr;
	}

	sprintf(total_buf, "%s %s %s \n", buf, log_levelp, log_msg);
	fprintf(fout, "%s", total_buf);
	fputs(total_buf, LOG.log_fp);
	// fwrite(total_buf, sizeof(total_buf) , 1, LOG.log_fp);
	fflush(LOG.log_fp);
	fflush(fout);
}

void log_error(const char *fmt, ...)
{
	char log_msg[LOG_MESSAGE_SIZE] = {0};
	va_list ap;

	SPIN_LOCK(&LOG);
	va_start(ap, fmt);
	zy_evutil_vsnprintf(log_msg, sizeof(log_msg), fmt, ap);
	_log(LOG_ERROR, log_msg);
	va_end(ap);
	SPIN_UNLOCK(&LOG);
}

void log_debug(const char *fmt, ...)
{
	char log_msg[LOG_MESSAGE_SIZE] = {0};
	va_list ap;

	SPIN_LOCK(&LOG);
	va_start(ap, fmt);
	zy_evutil_vsnprintf(log_msg, sizeof(log_msg), fmt, ap);
	_log(LOG_DEBUG, log_msg);
	va_end(ap);
	SPIN_UNLOCK(&LOG);
}

void log_info(const char *fmt, ...)
{
	char log_msg[LOG_MESSAGE_SIZE] = {0};
	va_list ap;

	SPIN_LOCK(&LOG);
	va_start(ap, fmt);
	zy_evutil_vsnprintf(log_msg, sizeof(log_msg), fmt, ap);
	_log(LOG_INFO, log_msg);
	va_end(ap);
	SPIN_UNLOCK(&LOG);
}

void log_warn(const char *fmt, ...)
{
	char log_msg[LOG_MESSAGE_SIZE] = {0};
	va_list ap;

	SPIN_LOCK(&LOG);
	va_start(ap, fmt);
	zy_evutil_vsnprintf(log_msg, sizeof(log_msg), fmt, ap);
	_log(LOG_WARN, log_msg);
	va_end(ap);
	SPIN_UNLOCK(&LOG);
}

void log_init(const char *logpath)
{
	LOG.logpath = logpath;
	LOG.log_fp = fopen(logpath, "a+");
	if (!LOG.log_fp) {
		fprintf(stderr, "open log failed,the logpath is (%s)\n", logpath);
		exit(1);
	}

	SPIN_INIT(&LOG);
}

void log_release()
{
	SPIN_DESTROY(&LOG);
	fclose(LOG.log_fp);
}