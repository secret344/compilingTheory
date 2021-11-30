#ifndef _Memory_Management_
#define _Memory_Management_
#include <stdlib.h>

extern void *my_malloc(size_t size);
extern void *my_calloc(size_t _Count, size_t _Size);
extern void my_free(void *ptr);
extern void printfM();
#endif