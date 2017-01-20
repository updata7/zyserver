#include "malloc.h"

void *Malloc(size_t size)
{
	return malloc(size);
}

void Free(void *ptr)
{
	free(ptr);
}