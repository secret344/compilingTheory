#ifndef _MY_SET_
#define _MY_SET_
#include "rb_tree.h"

typedef enum SetType
{
    Set_Number = RB_Number,
    Set_String = RB_String,
    Set_Struct = RB_Struct
} SetType;

typedef struct RbRoot *SetRoot;

SetRoot new_Set(SetType);

void removep_set(SetRoot root, void *k);
void removen_set(SetRoot root, int k);

void addp_set(SetRoot root, void *value);
void addn_set(SetRoot root, int value);

BOOL hasp_set(SetRoot root, void *k);
BOOL hasn_set(SetRoot root, int k);

My_Iterator *new_Point_Set_iterator(SetRoot root);
void *getp_Set_iterator_next(my_iterator itor);
int getn_Set_iterator_next(my_iterator itor);
int has_Set_iterator_next(my_iterator itor);

BOOL is_Set_Eq(SetRoot a, SetRoot b);

void set_destory(RbRoot *root, void (*handle)(void *));
#endif
