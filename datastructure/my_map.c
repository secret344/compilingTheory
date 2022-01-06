#include "my_map.h"

static MapRoot mapCreate(MapType type);
static void s_traversal_map(MapType type, RbNodeP node);
static void *get_node(MapRoot root, Rbkey key);

/**
 * @brief 新建map
 * map类型为key类型
 * 若类型为number时使用set_string_node会出大问题
 * 若类型为string时使用set_number_node也会出大问题
 * 
 * TODO：考虑一个map利用stack实现多类型key存储（暂时用不上）
 * [number_map,string_map] 获取时区分key 
 *
 * TODO：数字key可以转为字符串存储，或者实现hashMap,再想想，学习下别人的
 * @param type 
 * @return MapRoot 
 */
MapRoot newMap(MapType type)
{
    MapRoot root = rb_create((RBKeyType)type);
    return root;
}

My_Iterator *newMapIterator(MapRoot root)
{
    return new_rb_iterator(root);
}
/**
 * @brief 删除节点
 * @param k 
 * @param root 
 */
void MapNumRemove(MapRoot root, int k)
{
    Rbkey key;
    key.n = k;
    rb_delect_node(root, key);
}

void MapStrRemove(MapRoot root, char *k)
{
    Rbkey key;
    key.p = k;
    rb_delect_node(root, key);
}

/**
 * @brief 设置节点
 * @param k 
 * @param value 
 * @param root 
 */
void MapPutNumNode(MapRoot root, int k, void *value)
{
    Rbkey key;
    key.n = k;
    RBKeyType key_type = root->key_type;
    rb_insert_node(root, key, value);
}

/**
 * @brief 设置节点
 * 
 * @param k 
 * @param value 
 * @param root 
 */
void MapPutStrNode(MapRoot root, char *k, void *value)
{
    Rbkey key;
    key.p = k;
    rb_insert_node(root, key, value);
}

/**
 * @brief 获取节点
 * 同上
 * @param root 
 * @param k 
 * @return void* 
 */
void *MapGetNumNode(MapRoot root, int k)
{
    Rbkey key;
    key.n = k;
    return get_node(root, key);
}

void *MapGetStrNode(MapRoot root, char *k)
{
    Rbkey key;
    key.p = k;
    return get_node(root, key);
}

void *get_node(MapRoot root, Rbkey key)
{
    RbNodeP node = rb_search_node(root, key);
    if (node == NULL)
    {
        return NULL;
    }
    return node->value;
}