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

extern SetRoot new_Set(SetType);

extern void removep_set(SetRoot root, void *k);
extern void removen_set(SetRoot root, int k);

extern BOOL addp_set(SetRoot root, void *value);
extern BOOL addn_set(SetRoot root, int value);

extern BOOL hasp_set(SetRoot root, void *k);
extern BOOL hasn_set(SetRoot root, int k);

extern My_Iterator *new_Point_Set_iterator(SetRoot root);
extern void *getp_Set_iterator_next(my_iterator itor);
extern int getn_Set_iterator_next(my_iterator itor);
extern int has_Set_iterator_next(my_iterator itor);
#endif