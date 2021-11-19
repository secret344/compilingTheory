
#include "rb_tree.h"

static void rb_insert_fixup(RbRoot *root, RbNodeP node);
static BOOL rb_node_key_compare(RBKeyType key_type, RbNodeP a, RbNodeP b);

RbRoot *rb_create(RBKeyType key_type)
{
    RbRoot *root = (RbRoot *)my_malloc(sizeof(RbRoot));
    root->node = NULL;
    root->key_type = key_type;
    return root;
}

void rb_insert_node(RbRoot *root, RbNodeP node)
{
    RbNodeP current = NULL;
    RbNodeP x = root->node;
    // 寻找插入位置
    while (x != NULL)
    {
        current = x;
        if (rb_node_key_compare(root->key_type, node, current))
            x = x->left;
        else
            x = x->right;
    }
    node->parent = current;
    // 判断是左子节点还是右子节点 插入到 current 子节点中
    if (current != NULL)
    {
        if (rb_node_key_compare(root->key_type, node, current))
            current->left = node;
        else
            current->right = node;
    }
    else
    {
        root->node = node;
    }
    node->isRed = TRUE;
    // 进行自平衡
    rb_insert_fixup(root, node);
}
// 进行插入自平衡
void rb_insert_fixup(RbRoot *root, RbNodeP node)
{
    // 定义父节点，祖父节点
    RbNodeP parent, gparent;
    // 父节点存在 且为红色节点
    // 不存在则子身为根节点，不是红色节点则不需要自平衡
    while ((parent = node->parent) && parent->isRed)
    {
        gparent = parent->parent;
    }
}

RbNodeP rb_new_node()
{
    RbNodeP new = my_malloc(sizeof(RBNode));

    return new;
}

void rb_left_rotate() {}
void rb_right_rotate() {}

// 比较 a b 大小
// 大于 TRUE 小于等于 FALSE
BOOL rb_node_key_compare(RBKeyType key_type, RbNodeP a, RbNodeP b)
{
    BOOL result;
    switch (key_type)
    {
    // 结构体比较 比较地址 存放时只存放地址
    case RB_Struct:
    case RB_Number:
        result = a->key.n > b->key.n ? TRUE : FALSE;
        break;
    // 字符串比较 从左到右比较 左边字母越大自身越大
    case RB_String:
        result = string_compare_gt(a->key.p, b->key.p);
        if (result == COMPARE_EQ)
        {
            result = FALSE;
        }
        break;
    default:
        printf("红黑树节点KEY类型未定义");
        break;
    }
    return result;
}