
#include "my_set.h"
static void set_node(SetRoot root, Rbkey key, void *value);
static BOOL has_node(SetRoot root, Rbkey key);
static BOOL isp_Set_Eq(SetRoot a, SetRoot b);
static BOOL isn_Set_Eq(SetRoot a, SetRoot b);
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
 * @brief 清除set
 * 
 * @param root 
 * @param handle 
 */
void set_destory(RbRoot *root, void (*handle)(void *))
{
    SetType type = root->key_type;
    if (type == Set_Number)
    {
        // 数字类型不需要清除value
        rb_destory(root, NULL);
        return;
    }
    rb_destory(root, handle);
}

/**
 * @brief 设置指针节点
 * 包含字符串指针
 * 字符串指针与结构体指针比较方式不同 不能混合使用
 * @param k 
 * @param value 
 * @param root 
 */
void addp_set(SetRoot root, void *value)
{
    Rbkey key;
    RBKeyType key_type = root->key_type;;
    if (key_type == Set_Struct)
        key.n = (int)&*value;
    else
        key.p = value;

    return set_node(root, key, value);
}

void addn_set(SetRoot root, int value)
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
    RBKeyType key_type = root->key_type;
    if (key_type == Set_Struct)
        key.n = &*k;
    else
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
    RBKeyType key_type = root->key_type;
    if (key_type == Set_Struct)
        key.n = &*k;
    else
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

BOOL is_Set_Eq(SetRoot a, SetRoot b)
{
    BOOL result = TRUE;
    int n1 = a->size;
    int n2 = b->size;
    if (n1 != n2 || a->key_type != b->key_type)
    {
        return FALSE;
    }
    switch (a->key_type)
    {
    case Set_Number:
        return isn_Set_Eq(a, b);
    case Set_String:
    case Set_Struct:
        return isp_Set_Eq(a, b);
    default:
        return FALSE;
    }
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

BOOL isn_Set_Eq(SetRoot a, SetRoot b)
{
    My_Iterator *itorA = new_Point_Set_iterator(a);
    while (has_Set_iterator_next(itorA))
    {
        int n = getn_Set_iterator_next(itorA);
        if (!hasn_set(b, n))
        {
            return FALSE;
        }
    }
    return TRUE;
}

BOOL isp_Set_Eq(SetRoot a, SetRoot b)
{
    My_Iterator *itorA = new_Point_Set_iterator(a);
    while (has_Set_iterator_next(itorA))
    {
        void *n = getp_Set_iterator_next(itorA);
        if (!hasp_set(b, n))
        {
            return FALSE;
        }
    }
    return TRUE;
}

void set_node(SetRoot root, Rbkey key, void *value)
{
    rb_insert_node(root, key, value);
}
