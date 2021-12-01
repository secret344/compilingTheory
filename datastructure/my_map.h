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

MapRoot new_map(MapType type);
void removem_number_map(MapRoot root, int k);
void removem_string_map(MapRoot root, char *k);
void setm_number_node(MapRoot root, int k, void *value);
void setm_string_node(MapRoot root, char *k, void *value);
void traversal_map(MapRoot root);
void *getm_number_node(MapRoot root, int k);
void *getm_string_node(MapRoot root, char *k);
My_Iterator *new_Map_iterator(MapRoot root);
#endif