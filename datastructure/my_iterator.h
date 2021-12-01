#ifndef _MY_ITERATOR_
#define _MY_ITERATOR_
#include <stdio.h>
#include <stdlib.h>
#include "memory_management.h"

typedef void *(*GET_NEXT_HOOK_FUNC)(void *iter_instance, void *iter_inner);
typedef int (*HAS_NEXT_HOOK_FUNC)(void *iter_instance, void *iter_inner);

typedef struct My_Iterator
{
    void *iter_instance;
    void *iter_inner;
    GET_NEXT_HOOK_FUNC _get_next;
    HAS_NEXT_HOOK_FUNC _has_next;
} My_Iterator, *my_iterator;

My_Iterator *my_iterator_new(void *iter_instance, void *iter_inner, GET_NEXT_HOOK_FUNC g, HAS_NEXT_HOOK_FUNC h);

void *get_itor_next(my_iterator itor);
int has_itor_next(my_iterator itor);
void my_iterator_free(my_iterator itor);
#endif
