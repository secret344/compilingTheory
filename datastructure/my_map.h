#ifndef _MAP_
#define _MAP_
#include "rb_tree.h"
typedef void (*Set_Number_Node)(int, void *, RbRoot *);
typedef void (*Set_String_Node)(char *, void *, RbRoot *);

typedef enum MapType
{
    Map_Number = RB_Number,
    Map_String = RB_String
} MapType;

typedef struct RbRoot *MapRoot;

extern MapRoot new_map(MapType type);
extern void removem_number_map(MapRoot root, int k);
extern void removem_string_map(MapRoot root, char *k);
extern void setm_number_node(MapRoot root, int k, void *value);
extern void setm_string_node(MapRoot root, char *k, void *value);
extern void traversal_map(MapRoot root);
extern void *getm_number_node(MapRoot root, int k);
extern void *getm_string_node(MapRoot root, char *k);
extern My_Iterator *new_Map_iterator(MapRoot root);
#endif