#include <stdio.h>
#include "test_cb.h"

void reg(int param, func_cb cb);
void f(struct st *s);

int main()
{
	reg(1, f);
	return 0;
}

void reg(int param, func_cb cb)
{
	struct st s;
	s.a = param;
	cb(&s);
}

void f(struct st *s)
{
	int b = 6;
	b += s->a;
	printf("====> %d\n", b);
}