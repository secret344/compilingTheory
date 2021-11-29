
#include "rb_tree.h"

static int rb_node_key_compare(RBKeyType key_type, Rbkey key, RbNodeP b);
static void rb_left_rotate(RbRoot *root, RbNodeP node);
static void rb_right_rotate(RbRoot *root, RbNodeP node);
static void rb_delete_fixup(RbRoot *root, RbNodeP node, RbNodeP parent);
static void rb_insert_fixup(RbRoot *root, RbNodeP node);
static void rb_destory_static(RbNodeP node, void (*handle)(RbNodeP), RBKeyType type);
static RbNodeP rb_right_back(RbNodeP node);
static RbNodeP rb_set_next(RbNodeP cur);
static RbNodeP rb_get_next(void *iter_instance, void *iter_inner);
static RbNodeP rb_left_back(RbNodeP node);
static BOOL rb_has_next(void *iter_instance, void *iter_inner);
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

    free(root);
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
    new->value = value;
    new->isDelect = FALSE;

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
void rb_insert_node(RbRoot *root, RbNodeP node)
{
    RbNodeP current = NULL;
    RbNodeP x = root->node;
    // 寻找插入位置
    while (x != NULL)
    {
        current = x;
        if (rb_node_key_compare(root->key_type, node->key, x) == 0)
            x = x->left;
        else
            x = x->right;
    }
    node->parent = current;
    // 判断是左子节点还是右子节点 插入到 current 子节点中
    if (current != NULL)
    {
        if (rb_node_key_compare(root->key_type, node->key, current) == 0)
            current->left = node;
        else
            current->right = node;
    }
    else
    {
        root->node = node;
    }
    node->isRed = TRUE;
    root->size++;
    // 进行自平衡
    rb_insert_fixup(root, node);
}

/**
 * @brief  删除树节点
 * 保留标记删除属性项
 * @param root 
 * @param key 
 */
void rb_delect_node(RbRoot *root, Rbkey key)
{
    RbNodeP node = rb_search_node(root, key);
    if (node == NULL)
    {
        return;
    }

    RbNodeP child, parent;
    int color;
    // 存在左右子节点
    if (node->left != NULL && node->right != NULL)
    {
        RbNodeP replace = node;
        // 获取后继节点 替换需要删除的值
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;
        // 替换节点
        if (node->parent == NULL)
        {
            // 如果删除节点是根节点
            // 更新根节点
            root->node = replace;
        }
        else
        {
            // 如果删除节点不是根节点
            if (node->parent->left == node)
            {
                node->parent->left = replace;
            }
            else
            {
                node->parent->right = replace;
            }
        }

        // 保存"替换节点"的颜色 如果是黑色节点 表示红黑树不平衡
        color = replace->isRed;
        // 替换节点 是后继节点 所以不存在左子节点
        child = replace->right;
        // 保存替换节点的父亲节点
        parent = replace->parent;

        if (parent == node)
        {
            // 如果替换节点父亲节点就是当前删除节点
            parent = replace;
        }
        else
        {
            parent->left = child;
            replace->right = node->right;
            node->right->parent = replace;
        }

        replace->parent = node->parent;
        replace->isRed = node->isRed;
        replace->left = node->left;
        node->left->parent = replace;
    }
    else
    {
        if (node->left == NULL)
        {
            child = node->right;
        }
        else
        {
            child = node->left;
        }
        color = node->isRed;
        parent = node->parent;

        if (child)
        {
            child->parent = parent;
        }

        if (parent == NULL)
        {
            root->node = child;
        }
        else
        {
            // 如果删除节点不是根节点
            if (node->parent->left == node)
            {
                node->parent->left = child;
            }
            else
            {
                node->parent->right = child;
            }
        }
    }

    if (color == FALSE && child != NULL)
    {
        // 需要修正
        rb_delete_fixup(root, child, parent);
    }

    if (root->key_type == RB_String)
    {
        // 字符串key释放
        my_free(node->key.p);
    }
    root->size--;
    my_free(node);
}

/** 
 * 进行插入自平衡
 * @brief 
 * 1 插入节点的父节点和其叔叔节点（祖父节点的另一个子节点）均为红色。
 * 2 插入节点的父节点是红色的，叔叔节点是黑色的，且插入节点是其父节点的右子节点。
 * 3 插入节点的父节点是红色的，叔叔节点是黑色的，且插入节点是其父节点的左子节点。
 * @param root 
 * @param node 
 */
void rb_insert_fixup(RbRoot *root, RbNodeP node)
{
    // 定义父节点，祖父节点
    RbNodeP parent, gparent;
    // 父节点存在 且为红色节点
    // 不存在则子身为根节点，不是红色节点则不需要自平衡
    while ((parent = node->parent) && parent->isRed)
    {
        gparent = parent->parent;
        // 区分node父节点是祖父节点的左右子节点状态
        // 叔叔节点的获取不同 旋转方向不同
        if (gparent->left == parent)
        {
            RbNodeP uncle = gparent->right;
            // 叔叔节点红色 状态1
            if (uncle && uncle->isRed)
            {
                uncle->isRed = FALSE;
                parent->isRed = FALSE;
                gparent->isRed = TRUE;
                // 颜色变化结束，检查祖父节点平衡状态
                node = gparent;
                continue;
            }
            // 状态2
            // 父节点是红色的，叔叔节点是黑色的，且插入节点是其父节点的右子节点
            if (parent->right == node)
            {
                // 左旋
                rb_left_rotate(root, parent);
                // 将自己与父节点调换位置
                RbNodeP tmp = parent;
                parent = node;
                node = tmp;
            }
            // 状态3
            // 父节点是红色的，叔叔节点是黑色的，且插入节点是其父节点的左子节点
            parent->isRed = FALSE;
            gparent->isRed = TRUE;
            rb_right_rotate(root, gparent);
        }
        else
        {
            RbNodeP uncle = gparent->left;
            if (uncle && uncle->isRed)
            {
                uncle->isRed = FALSE;
                parent->isRed = FALSE;
                gparent->isRed = TRUE;
                node = gparent;
                continue;
            }
            if (parent->left == node)
            {
                rb_right_rotate(root, parent);
                RbNodeP tmp = parent;
                parent = node;
                node = tmp;
            }
            parent->isRed = FALSE;
            gparent->isRed = TRUE;
            rb_left_rotate(root, gparent);
        }
    }
    // 根节点设黑色
    root->node->isRed = FALSE;
}
/**
 * @brief 删除修正
 * 
 * @param root 
 * @param node 
 * @param parent 
 */
void rb_delete_fixup(RbRoot *root, RbNodeP node, RbNodeP parent)
{
    RbNodeP sibling;
    while (node == NULL || node->isRed == FALSE && node != root->node)
    {
        if (parent->left == node)
        {
            sibling = parent->right;
            if (sibling->isRed == TRUE)
            {
                // 场景2.1:兄弟节点是红色
                // 兄弟节点设置为黑色
                sibling->isRed = FALSE;
                parent->isRed = TRUE;
                rb_left_rotate(root, parent);
                sibling = parent->right;
            }
            // 场景2.4: 兄弟节点两个子节点都是黑色
            // node的兄弟节点是黑色的切2个子节点也是黑色的
            if ((sibling->right == NULL || sibling->right->isRed == FALSE) && (sibling->left == NULL || sibling->left->isRed == FALSE))
            {
                sibling->isRed = TRUE;
                //再次以父节点为新节点作自平衡处理。
                node = parent;
                parent = node->parent;
                continue;
            }
            else if (sibling->right == NULL || sibling->right->isRed == FALSE)
            {
                // node的兄弟sibling是黑色的，并且sibling的左孩子是红色，右孩子为黑色。
                // 场景2.3: 兄弟节点的左子节点是黑色，转换到场景2.2.
                // 替换节点的兄弟节点sibling设置成红色，兄弟节点的左子节点 SL 设置为黑色，再对节点 S 右旋操作，转换到了场景 2.2
                sibling->left->isRed = FALSE;
                sibling->isRed = TRUE;
                rb_right_rotate(root, sibling);
                sibling = parent->right;
            }

            if (sibling->right && sibling->right->isRed == TRUE)
            {
                //场景2.2：兄弟节点的右节点是红色
                // node的兄弟sibling是黑色的；并且sibling的右孩子是红色的，左孩子任意颜色。
                sibling->isRed = parent->isRed;
                parent->isRed = FALSE;
                sibling->isRed = FALSE;
                rb_left_rotate(root, parent);
                node = root->node;
            }
        }
        else
        {
            // 节点是父节点的右子节点
            sibling = parent->left;
            // 场景 3.1：替换节点的兄弟节点是红色
            if (sibling->isRed == TRUE)
            {
                sibling->isRed = FALSE;
                parent->isRed = TRUE;
                rb_right_rotate(root, parent);
                sibling = parent->left;
            }
            // 场景3.4：替换节点的两个子节点都是黑色
            if ((sibling->right == NULL || sibling->right->isRed == FALSE) && (sibling->left == NULL || sibling->left->isRed == FALSE))
            {
                sibling->isRed = TRUE;
                node = parent;
                parent = node->parent;
                continue;
            }
            else if (sibling->left == NULL || sibling->left->isRed == FALSE)
            {
                // 场景3.3:兄弟节点的右子节点是红色
                sibling->right->isRed = FALSE;
                sibling->isRed = TRUE;
                rb_left_rotate(root, sibling);
                sibling = parent->left;
            }

            if (sibling->left && sibling->left->isRed == TRUE)
            {
                // 场景3.2：兄弟节点的左子节点是红色
                sibling->isRed = parent->isRed;
                parent->isRed = FALSE;
                sibling->left->isRed = FALSE;
                rb_right_rotate(root, parent);
                node = root->node;
            }
        }
    }
    if (node != NULL)
    {
        node->isRed = FALSE;
    }
}
/* 
 * 对红黑树的节点(node下图 x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y                
 *   /  \      --(左旋)-->           / \                #
 *  lx   y                          x  ry     
 *     /   \                       /  \
 *    ly   ry                     lx  ly  
 *
 *
 */
void rb_left_rotate(RbRoot *root, RbNodeP node)
{
    // 拿到节点的右子节点
    RbNodeP y = node->right;
    // 将右子节点的左子节点设为他的右子节点
    node->right = y->left;
    // 判断是否为NULL，如果不是NULL设置右子节点的左子节点父亲节点为node
    if (y->left != NULL)
    {
        y->left->parent = node;
    }
    // 将node右子节点的父节点设置为node的父节点
    // 移动到node自己头上
    y->parent = node->parent;
    // node不存在父亲节点(意思就是他是根节点)，将右子节点设置为根节点
    if (node->parent == NULL)
    {
        root->node = y;
    }
    else
    {
        // 判断node是左子节点还是右子节点
        // 旋转替代node节点位置用
        if (node->parent->left == node)
        {
            node->parent->left = y;
        }
        else
        {
            node->parent->right = y;
        }
    }
    // 链接node跟转移后的node右子节点
    y->left = node;
    node->parent = y;
}

/* 
 * 对红黑树的节点(node 下图 y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *          y                                x                  
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y  
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 * 
 */
void rb_right_rotate(RbRoot *root, RbNodeP node)
{
    // 保存node的左子节点
    // 左旋右旋对称 流程差不多
    RbNodeP x = node->left;
    node->left = x->right;
    if (x->right != NULL)
    {
        x->right->parent = node;
    }
    x->parent = node->parent;
    if (node->parent == NULL)
    {
        root->node = x;
    }
    else
    {
        if (node->parent->left == node)
        {
            node->parent->left = x;
        }
        else
        {
            node->parent->right = x;
        }
    }
    x->right = node;
    node->parent = x;
}

void rb_destory_static(RbNodeP node, void (*handle)(RbNodeP), RBKeyType type)
{
    if (node->left != NULL)
    {
        rb_destory_static(node->left, handle, type);
    }
    if (node->right != NULL)
    {
        rb_destory_static(node->right, handle, type);
    }
    handle(node);

    if (type == RB_String)
    {
        // 字符串key释放
        my_free(node->key.p);
    }

    free(node);
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
