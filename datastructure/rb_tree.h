#ifndef _RB_TREE_
#define _RB_TREE_
#include "memory_management.h"
#include "bool.h"
#include "data_struct_utils.h"
#include <stdio.h>

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
} RbRoot;

extern RbRoot *rb_create(RBKeyType key_type);
extern RbNodeP rb_new_node(Rbkey key, void *value);
extern void rb_insert_node(RbRoot *root, RbNodeP node);
extern void rb_delect_node(RbRoot *root, Rbkey key);
extern void rb_destory(RbRoot *root, void (*handle)(RbNodeP));
#endif