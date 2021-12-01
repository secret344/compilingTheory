#ifndef _Memory_Management_
#define _Memory_Management_
#include <stdlib.h>

void *my_malloc(size_t size);
void *my_calloc(size_t _Count, size_t _Size);
void my_free(void *ptr);
void printfM();
#endif