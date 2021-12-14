
#include "rb_tree.h"

static int rb_node_key_compare(RBKeyType key_type, Rbkey key, RbNodeP b);
static void rb_destory_static(RbNodeP node, void (*handle)(void *), RBKeyType type);
static RbNodeP rb_right_back(RbNodeP node);
static RbNodeP rb_set_next(RbNodeP cur);
static RbNodeP rb_get_next(void *iter_instance, void *iter_inner);
static RbNodeP rb_left_back(RbNodeP node);
static BOOL rb_has_next(void *iter_instance, void *iter_inner);

static RbNodeP rb_new_node(RBKeyType type, Rbkey key, void *value);
static RbNodeP balance(RbNodeP h);
static void flipColors(RbNodeP node);
static RbNodeP rb_left_rotate(RbNodeP node);
static RbNodeP rb_right_rotate(RbNodeP node);
static RbNodeP rb_move_red_to_left(RbNodeP h);
static RbNodeP rb_move_red_to_right(RbNodeP h);
static RbNodeP min_node(RbNodeP h);
static RbNodeP rb_delect(RBKeyType key_type, RbNodeP h, Rbkey key);
static RbNodeP rb_insert(RbRoot *root, RbNodeP h, Rbkey key, void *value);

/**
 * @brief 创建红黑树根
 * 
 * @param key_type 
 * @return RbRoot* 
 */
RbRoot *rb_create(RBKeyType key_type)
{
    RbRoot *root = (RbRoot *)my_malloc(sizeof(RbRoot));
    root->node = NULL;
    root->size = 0;
    root->key_type = key_type;
    return root;
}

/**
 * @brief 卸载红黑树
 * 
 * @param root 
 * @param handle 
 */
void rb_destory(RbRoot *root, void (*handle)(RbNodeP))
{
    if (root == NULL)
    {
        return;
    }

    RbNodeP node = root->node;
    RBKeyType type = root->key_type;
    if (node != NULL)
    {
        rb_destory_static(node, handle, type);
    }

    my_free(root);
}

/**
 * @brief 查找节点
 * 
 * @param root 
 * @param key 
 * @return RbNodeP 
 */
RbNodeP rb_search_node(RbRoot *root, Rbkey key)
{
    RBKeyType key_type = root->key_type;
    RbNodeP node = root->node;

    while (node)
    {
        int result = rb_node_key_compare(key_type, key, node);
        if (result == TRUE)
        {
            node = node->right;
        }
        else if (result == FALSE)
        {
            node = node->left;
        }
        else
        {
            break;
        }
    }

    return node;
}

/**
 * @brief 新建树节点
 * 新建节点key需要跟树节点相同
 * @param key 
 * @param value 
 * @return RbNodeP 
 */
RbNodeP rb_new_node(RBKeyType type, Rbkey key, void *value)
{

    RbNodeP new = my_malloc(sizeof(RBNode));
    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;
    new->value = &*value;
    new->isDelect = FALSE;
    new->isRed = TRUE;

    if (type == RB_String)
    {
        // 字符串需要拷贝
        char *p = key.p;
        key.p = (char *)my_malloc(strlen(p) + 1);
        strcpy(key.p, p);
    }

    new->key = key;
    return new;
}

/**
 * @brief 生成迭代器
 * 使用迭代器期间不能对rb_tree做增加删除
 * 会导致意想不到的后果
 * @param root 
 * @return My_Iterator* 
 */
My_Iterator *new_rb_iterator(RbRoot *root)
{
    rb_iter_inner p = NULL;
    p = my_malloc(sizeof(*p));
    if (!p)
        return NULL;
    p->item = root->node;
    return my_iterator_new(root, p, (GET_NEXT_HOOK_FUNC)rb_get_next, (HAS_NEXT_HOOK_FUNC)rb_has_next);
}

/**
 * @brief 插入节点
 * 
 * @param root 
 * @param node 
 */
void rb_insert_node(RbRoot *root, Rbkey key, void *value)
{
    root->node = rb_insert(root, root->node, key, value);
    root->node->isRed = FALSE;
}

/**
 * @brief  删除树节点
 * 保留标记删除属性项
 * @param root 
 * @param key 
 */
void rb_delect_node(RbRoot *root, Rbkey key)
{
    if (rb_search_node(root, key) == NULL)
    {
        return;
    }
    if (!IsRed(root->node->left) && !IsRed(root->node->right))
        root->node->isRed = TRUE;
    root->node = rb_delect(root->key_type, root->node, key);
    root->size--;
    if (root->size > 0)
    {
        root->node->isRed = FALSE;
    }
}

RbNodeP rb_insert(RbRoot *root, RbNodeP h, Rbkey key, void *value)
{
    RBKeyType key_type = root->key_type;
    if (h == NULL)
    {
        root->size++;
        return rb_new_node(key_type, key, value);
    }
    // 大于 1 小于 0 等于 -1
    int cmp = rb_node_key_compare(key_type, key, h);
    if (cmp == FALSE)
    {
        // 小于 往树左子节点走
        h->left = rb_insert(root, h->left, key, value);
        SetParent(h->left, h);
    }
    else if (cmp == TRUE)
    {
        // 大于 往树右子节点走
        h->right = rb_insert(root, h->right, key, value);
        SetParent(h->right, h);
    }
    else
    {
        // 相等节点 替换value
        h->value = value;
    }
    // 添加完成 进行递归修正
    h = balance(h);
    return h;
}

static RbNodeP deleteMin(RbNodeP node)
{
    if (node->left == NULL)
    {
        my_free(node);
        return NULL;
    }
    if (!IsRed(node->left) && !IsRed(node->right))
        node = rb_move_red_to_left(node);
    node->left = deleteMin(node->left);
    return balance(node);
}

RbNodeP rb_delect(RBKeyType key_type, RbNodeP h, Rbkey key)
{
    if (rb_node_key_compare(key_type, key, h) == FALSE)
    {
        // 在左子树中 如果左子树不是3节点
        if (!IsRed(h->left) && !IsRed(h->left->left))
        {
            h = rb_move_red_to_left(h);
        }
        // 继续查找左子树
        h->left = rb_delect(key_type, h->left, key);
    }
    else
    {
        // 找到 或者在右子树中
        //  将左边的红链接 变成右边的
        if (IsRed(h->left))
            h = rb_right_rotate(h);

        if (rb_node_key_compare(key_type, key, h) == COMPARE_EQ && h->right == NULL)
        {
            // 找到了 且不存在右子节点
            my_free(h);
            return NULL;
        }

        // 右子节点不是3节点
        if (!IsRed(h->right) && !IsRed(h->right->left))
        {
            h = rb_move_red_to_right(h);
        }

        if (rb_node_key_compare(key_type, key, h) == COMPARE_EQ)
        {
            RbNodeP x = min_node(h->right); //找到后继节点
            h->key = x->key;
            h->value = x->value;
            h->right = deleteMin(h->right); // 在右子树中删除后继;
        }
        else
            h->right = rb_delect(key_type, h->right, key);
    }

    return balance(h);
}

// 查找后继节点
RbNodeP min_node(RbNodeP h)
{
    if (h->left != NULL)
        return min_node(h->left);
    else
        return h;
}

RbNodeP rb_move_red_to_left(RbNodeP h)
{
    flipColors(h);
    if (IsRed(h->right->left))
    {
        // 如果右儿子为3 - 节点
        //通过两次旋转将替代者上移至h处
        h->right = rb_right_rotate(h->right);
        h = rb_left_rotate(h);
        flipColors(h); //#分裂5 - 节点
    }
    return h;
}

RbNodeP rb_move_red_to_right(RbNodeP h)
{
    flipColors(h);
    if (IsRed(h->left->left))
    {
        h = rb_right_rotate(h); // h的左儿子就是替代者
        flipColors(h);
    }

    return h;
}

void flipColors(RbNodeP node)
{
    node->isRed = FlipBool(node->isRed);
    node->left->isRed = FlipBool(node->left->isRed);
    node->right->isRed = FlipBool(node->right->isRed);
}
/* 
 * 对红黑树的节点进行左旋转
 * 保证二叉搜索树和红黑树的性质的前提下，来转换红链接的位置
 */
RbNodeP rb_left_rotate(RbNodeP node)
{
    RbNodeP x = node->right;
    SetParent(x, node->parent);

    node->right = x->left;
    SetParent(x->left, node);

    x->left = node;
    SetParent(node, x);

    x->isRed = x->left->isRed;
    x->left->isRed = TRUE;
    return x;
}

/* 
 * 对红黑树的节点进行右旋转
 */
RbNodeP rb_right_rotate(RbNodeP node)
{
    RbNodeP x = node->left;
    SetParent(x, node->parent);

    node->left = x->right;
    SetParent(x->right, node);

    x->right = node;
    SetParent(node, x);

    x->isRed = x->right->isRed;
    x->right->isRed = TRUE;
    return x;
}

RbNodeP balance(RbNodeP h)
{
    // 1 右儿子红色 左儿子黑色
    // 左旋 让右子节点旋转到左边
    if (IsRed(h->right) && !IsRed(h->left))
        h = rb_left_rotate(h);

    // 2 左儿子红 左儿子的左儿子也红 (4节点)
    // 右旋 进入3
    if (IsRed(h->left) && IsRed(h->left->left))
        h = rb_right_rotate(h);
    // 3 左儿子红右儿子红 (4节点)
    // 颜色反转
    if (IsRed(h->right) && IsRed(h->left))
        flipColors(h);
    return h;
}

void rb_destory_static(RbNodeP node, void (*handle)(void *), RBKeyType type)
{
    if (node == NULL)
    {
        return;
    }

    if (node->left != NULL)
    {
        rb_destory_static(node->left, handle, type);
    }
    if (node->right != NULL)
    {
        rb_destory_static(node->right, handle, type);
    }

    if (handle != NULL)
    {
        handle(node->value);
    }

    if (type == RB_String)
    {
        // 字符串key释放
        my_free(node->key.p);
    }

    my_free(node);
}
/**
 * @brief 比大小
 * 大于 1 小于 0  等于 -1
 * @param key_type 
 * @param key 
 * @param b 
 * @return int 
 */
int rb_node_key_compare(RBKeyType key_type, Rbkey key, RbNodeP b)
{
    BOOL result;
    switch (key_type)
    {
    // 结构体比较 比较地址 存放时只存放地址
    case RB_Struct:
    case RB_Number:
        result = key.n > b->key.n ? TRUE : key.n == b->key.n ? COMPARE_EQ
                                                             : FALSE;
        break;
    // 字符串比较 从左到右比较 左边字母越大自身越大
    case RB_String:
        result = string_compare_gt(key.p, b->key.p);
        break;
    default:
        printf("红黑树节点KEY类型未定义");
        break;
    }
    return result;
}

/**
 * @brief 查找下一个节点
 * 
 * @param iter_instance 
 * @param iter_inner 
 * @return RbNodeP 
 */
RbNodeP rb_get_next(void *iter_instance, void *iter_inner)
{
    rb_iter_inner p = (rb_iter_inner)iter_inner;
    RbNodeP item = p->item;

    p->item = rb_set_next(item);

    return item;
}
RbNodeP rb_left_back(RbNodeP node)
{
    RbNodeP parent = node->parent;
    if (parent->right)
    {
        return parent->right;
    }
    else
    {
        if (parent->parent == NULL)
            return NULL;
        if (parent->parent->left == parent)
        {
            return rb_left_back(parent);
        }
        return rb_right_back(parent);
    }
}

RbNodeP rb_right_back(RbNodeP node)
{
    // 右子节点回退
    RbNodeP parent = node->parent;
    if (parent == NULL || parent->parent == NULL)
    {
        // 根节点说明遍历结束
        return NULL;
    }
    if (parent->parent->left == parent)
    {
        // 如果父节点是左子节点 返回左子节点回退结果
        return rb_left_back(parent);
    }
    // 如果父节点是右子节点 继续回退
    return rb_right_back(parent);
}

RbNodeP rb_set_next(RbNodeP cur)
{
    if (cur == NULL)
    {
        return NULL;
    }
    // 存在左子节点
    if (cur->left)
        return cur->left;
    // 存在右子节点
    if (cur->right)
        return cur->right;
    // 都不存在
    RbNodeP parent = cur->parent;
    if (parent && parent->left == cur)
    {
        return rb_left_back(cur);
    }
    return rb_right_back(cur);
}

BOOL rb_has_next(void *iter_instance, void *iter_inner)
{
    rb_iter_inner p = (rb_iter_inner)iter_inner;
    if (p->item == NULL)
    {
        return FALSE;
    }
    return TRUE;
}
