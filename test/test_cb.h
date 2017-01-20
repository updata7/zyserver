#ifndef _TEST_CB_H_
#define _TEST_CB_H_

struct st {
	int a;
};

typedef void (*func_cb)(struct st *);

#endif 	// _TEST_CB_H_