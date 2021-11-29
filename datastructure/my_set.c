
#include "my_set.h"
static BOOL set_node(SetRoot root, Rbkey key, void *value);
static BOOL has_node(SetRoot root, Rbkey key);
/**
 * @brief 
 * 区分数字指针类型
 * 还未想好
 * @return SetRoot 
 */
SetRoot new_Set(SetType type)
{
    SetRoot root = rb_create((RBKeyType)type);
    return root;
}

/**
 * @brief 设置指针节点
 * 包含字符串指针
 * 字符串指针与结构体指针比较方式不同 不能混合使用
 * @param k 
 * @param value 
 * @param root 
 */
BOOL addp_set(SetRoot root, void *value)
{
    Rbkey key;
    key.p = value;
    return set_node(root, key, value);
}
BOOL addn_set(SetRoot root, int value)
{
    Rbkey key;
    key.n = value;
    return set_node(root, key, NULL);
}

/**
 * @brief 删除节点
 * @param k 
 * @param root 
 */
void removep_set(SetRoot root, void *k)
{
    Rbkey key;
    key.p = k;
    rb_delect_node(root, key);
}
void removen_set(SetRoot root, int k)
{
    Rbkey key;
    key.n = k;
    rb_delect_node(root, key);
}
/**
 * @brief 获取节点
 * 同上
 * @param root 
 * @param k 
 * @return void* 
 */
BOOL hasp_set(SetRoot root, void *k)
{
    Rbkey key;
    key.p = k;
    return has_node(root, key);
}
BOOL hasn_set(SetRoot root, int k)
{
    Rbkey key;
    key.n = k;
    return has_node(root, key);
}

BOOL has_node(SetRoot root, Rbkey key)
{
    RbNodeP node = rb_search_node(root, key);
    if (node == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL set_node(SetRoot root, Rbkey key, void *value)
{
    BOOL v = has_node(root, key);
    if (!v)
    {
        rb_insert_node(root, rb_new_node(root->key_type, key, value));
        return TRUE;
    }
    return FALSE;
}

My_Iterator *new_Point_Set_iterator(SetRoot root)
{
    return new_rb_iterator(root);
}
/**
 * @brief 获取迭代器next
 * point返回指针  number返回int
 * 不存在返回NULL
 * @param itor 
 * @return void* 
 */
void *getp_Set_iterator_next(my_iterator itor)
{
    RbNodeP n = itor->_get_next(itor->iter_instance, itor->iter_inner);
    return n->value;
}
int getn_Set_iterator_next(my_iterator itor)
{
    RbNodeP n = itor->_get_next(itor->iter_instance, itor->iter_inner);
    return n->key.n;
}

int has_Set_iterator_next(my_iterator itor)
{
    return has_itor_next(itor);
}
