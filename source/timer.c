#include "timer.h"
#include "malloc.h"
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

#define zy_uint64_t int64_t
#define zy_uint32_t int32_t
#define zy_gettimeofday gettimeofday

struct timer {
	zy_uint64_t currenttime; 	// 当前时间戳
	zy_uint64_t starttime; 	// 启动时的时间戳
};

struct timer_f {
	timer_execute_func func;
	void *userdata;
	zy_uint32_t interval_time; 		// 间隔多少时间执行一次
	zy_uint32_t last_call_time; 	// 上一次执行时间;
	struct timer_f *next;
};

struct timer *T = NULL;

struct timer_f *TF = NULL;

zy_uint64_t get_currenttime()
{
	return T->currenttime;
}

zy_uint64_t get_starttime()
{
	return T->starttime;
}

void timer_init()
{
	// 初始化时间
	T = (struct timer *)Malloc(sizeof(struct timer));
	struct timeval tv;
	zy_gettimeofday(&tv, NULL);
	T->currenttime = tv.tv_sec * 1000 + tv.tv_usec / 10000;
	T->starttime = tv.tv_sec * 1000 + tv.tv_usec / 10000;
}

void timer_update()
{
	struct timeval tv;
	zy_gettimeofday(&tv, NULL);
	T->currenttime = tv.tv_sec * 1000 + tv.tv_usec / 10000;

	// 处理定时函数
	struct timer_f *tf = TF;
	while(tf) {
		if (tf->interval_time <= (T->currenttime - tf->last_call_time)) {
			tf->func(tf->userdata);
			tf->last_call_time = T->currenttime;
		}
		tf = tf->next;
	}
}

void timer_register(timer_execute_func func, void *userdata, int interval_time)
{
	if (TF == NULL) {
		TF = (struct timer_f *)Malloc(sizeof(struct timer_f));
		TF->func = func;
		TF->userdata = userdata;
		TF->interval_time = interval_time;
		TF->last_call_time = T->currenttime;
		TF->next = NULL;
	} else {
		struct timer_f *tf = TF;
		while (tf->next) {
			tf = tf->next;
		}

		struct timer_f *t = (struct timer_f *)Malloc(sizeof(struct timer_f));
		t->func = func;
		t->userdata = userdata;
		t->interval_time = interval_time;
		t->last_call_time = T->currenttime;
		tf->next = t;
		t->next = NULL;
	}
}

void timer_release()
{
	Free(T);

	struct timer_f *tf;
	while (TF) {
		tf = TF->next;
		Free(TF);
		TF = tf;
	}
}