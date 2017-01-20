#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#define as_root(N, K) 	\
	int N ## _ ## K ## _as_root() { return 3; };

void test_ch()
{
	char ch[7];
	ch[0] = 'R';
	char sp[6] = {0};
	sprintf(sp, "0x%04X", 1);
	strcpy(&ch[1], sp);

	int b = atoi("0001");
	long bb = strtol("0x0001", NULL, 16);
	printf("====%s b(%d) bb(%ld)\n", ch, b, bb);
}

struct func_t {
	void (*f)(int *a);
	int *a;
};

void func(int *a)
{
	printf("%d\n", *a);
}


int main(int argc, char *argv[])
{
	int n = 5;
	int i;
	int a[5] = {0};
	printf("==== ===\n");
	struct func_t t[5];
	for (i = 0; i < n; i++) {
		a[i] = i + 10;
		t[i].a = &a[i];
		t[i].f = func;
		break;
	}

	i++;

	int j;
	for (j = 0; j < i; j ++) {
		t[j].f(t[j].a);
	}

	return 0;
}