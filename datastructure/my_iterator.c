#include "my_iterator.h"

My_Iterator *my_iterator_new(void *iter_instance, void *iter_inner, GET_NEXT_HOOK_FUNC g, HAS_NEXT_HOOK_FUNC h)
{
    my_iterator itor = NULL;
    itor = (my_iterator)my_malloc(sizeof(My_Iterator));
    if (!itor)
        return NULL;
    itor->iter_inner = iter_inner;
    itor->iter_instance = iter_instance;
    itor->_get_next = g;
    itor->_has_next = h;
    return itor;
}

void *get_itor_next(my_iterator itor)
{
    return itor->_get_next(itor->iter_instance, itor->iter_inner);
}

int has_itor_next(my_iterator itor)
{
    return itor->_has_next(itor->iter_instance, itor->iter_inner);
}

void my_iterator_free(my_iterator itor)
{
    if (itor)
    {
        if (itor->iter_inner)
            my_free(itor->iter_inner);
        my_free(itor);
    }
}
