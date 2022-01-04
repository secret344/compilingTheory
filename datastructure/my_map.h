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

MapRoot newMap(MapType type);
void MapNumRemove(MapRoot root, int k);
void MapStrRemove(MapRoot root, char *k);
void MapPutNumNode(MapRoot root, int k, void *value);
void MapPutStrNode(MapRoot root, char *k, void *value);
void *MapGetNumNode(MapRoot root, int k);
void *MapGetStrNode(MapRoot root, char *k);
My_Iterator *newMapIterator(MapRoot root);
#endif