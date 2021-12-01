#include <stdio.h>
#include <stdlib.h>
static int countM = 0;
void *my_malloc(size_t size)
{
    countM++;
    return malloc(size);
}

void *my_calloc(size_t _Count, size_t _Size)
{
    countM++;
    return calloc(_Count, _Size);
}

void my_free(void *ptr)
{
    countM--;
    free(ptr);
}

void printfM()
{
    printf("内存情况（malloc次数与free次数差值）： %d\n", countM);
}