#ifndef MALLOC_H_
#define MALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

#include <stdlib.h>
#include <sys/types.h>
	
void *Malloc(size_t size);
void Free(void *ptr);

#ifdef __cplusplus
}
#endif 	// __cplusplus

#endif // MALLOC_H_