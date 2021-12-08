#ifndef _RB_TREE_
#define _RB_TREE_
#include "memory_management.h"
#include "bool.h"
#include "data_struct_utils.h"
#include <stdio.h>
#include <string.h>
#include "my_iterator.h"
#define IsRed(h) ((h == NULL || h->isRed == FALSE) ? FALSE : TRUE)
#define FlipBool(b) (b == TRUE ? FALSE : TRUE)
#define SetParent(n, p)    \
    {                      \
        if (n != NULL)     \
            n->parent = p; \
    }


typedef enum RBKeyType
{
    RB_Number = (1 << 1),
    RB_String = (1 << 2),
    RB_Struct = (1 << 3)
} RBKeyType;

typedef union Rbkey
{
    int n;
    char *p;
} Rbkey;

typedef struct RBNode
{
    BOOL isRed : 1;
    BOOL isDelect : 1; // 标记删除
    void *value;
    Rbkey key;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
} RBNode, *RbNodeP;

typedef struct RbRoot
{
    RbNodeP node;
    RBKeyType key_type;
    int size; // 树节点数量  insert +1 delect -1
} RbRoot;

typedef struct Rb_Iter_Inner
{
    RbNodeP item;
} Rb_Iter_Inner, *rb_iter_inner;

RbRoot *rb_create(RBKeyType key_type);
RbNodeP rb_search_node(RbRoot *root, Rbkey key);
void rb_insert_node(RbRoot *root, Rbkey key, void *value);
void rb_delect_node(RbRoot *root, Rbkey key);
void rb_destory(RbRoot *root, void (*handle)(RbNodeP));
My_Iterator *new_rb_iterator(RbRoot *root);
#endif