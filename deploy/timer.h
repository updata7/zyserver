#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif 	// __cplusplus

typedef void (*timer_execute_func)(void *userdata);

void timer_init();
void timer_update();
void timer_register(timer_execute_func func, void *userdata, int interval_time);
void timer_release();

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif 	// TIMER_H