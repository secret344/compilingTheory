#include "my_ArrayList.h"
static void grow(My_ArrayList *array);
static void ArrayListPrune(My_ArrayList *array);

/**
 * @brief 
 * 数据连续推荐使用，分散且有隔断建议使用map
 * @return My_ArrayList* 
 */
My_ArrayList *ArrayListCreate()
{
    My_ArrayList *array = my_malloc(sizeof(My_ArrayList));
    array->size = 0;
    array->capacity = 0;
    array->data = NULL;
    grow(array);
    return array;
}
/**
 * @brief 数组push元素
 * 
 * @param array 
 * @param node 
 * @return BOOL 
 */
BOOL ArrayListPush(My_ArrayList *array, MyArrayListNode *node)
{
    if (array == NULL)
        return FALSE;
    if (array->size >= array->capacity)
        grow(array);
    if (array->size < array->capacity)
    {
        array->data[array->size++] = node;
        return TRUE;
    }
    printf("数组容量扩展异常");
    return FALSE;
}
/**
 * @brief 数组取出最后一位元素
 * 
 * @param array 
 * @return MyArrayListNode* 
 */
MyArrayListNode *ArrayListPop(My_ArrayList *array)
{
    if (array == NULL || array->size == 0)
        return NULL;
    MyArrayListNode *result = array->data[array->size - 1];
    array->size--;
    // 当多余空间大于 2 * DEFAULT_CAPACITY 时，进行修剪
    if (array->capacity - array->size >= 2 * DEFAULT_CAPACITY)
        ArrayListPrune(array);
    return result;
}
/**
 * @brief 依据下标取出元素
 * 
 * @param array 
 * @param pos 
 * @return MyArrayListNode* 
 */
MyArrayListNode *ArrayListGetFormPos(My_ArrayList *array, int pos)
{
    if (array == NULL || pos < 0 || array->size <= pos)
        return NULL;
    MyArrayListNode *result = array->data[pos];
    return result;
}
/**
 * @brief 依据下标删除元素
 * 
 * @param array 
 * @param pos 
 * @return MyArrayListNode* 
 */
MyArrayListNode *ArrayListDelete(My_ArrayList *array, int pos)
{
    if (array == NULL || pos < 0 || array->size <= pos)
        return NULL;
    MyArrayListNode *result = array->data[pos];
    for (size_t i = pos + 1; i < array->size; i++)
    {
        array->data[i - 1] = array->data[i];
    }
    array->size--;
    return result;
}
/**
 * @brief 释放数组空间，不会对已经添加进入的数组元素操作
 * 
 * @param array 
 */
void ArrayListDestroy(My_ArrayList *array)
{
    if (array == NULL)
        return;
    if (array->data != NULL)
        my_free(array->data);
    my_free(array);
}

void ArrayListPrune(My_ArrayList *array)
{
    if (array == NULL)
        return -1;
    int mod = array->size % 10;
    int div = (int)(array->size / 10);
    if (mod > 0)
        div += 1;
    void *new = realloc(array->data, div * DEFAULT_CAPACITY);
    // 重新分配内存
    if (new != NULL)
    {
        array = new;
        array->capacity = div * DEFAULT_CAPACITY;
    }
}

/**
 * @brief 
 * 扩充失败数组容量不会发生变化
 * @param array 
 * @param capacity 所要扩大的大小
 */
void grow(My_ArrayList *array)
{
    int newBase = array->capacity + DEFAULT_CAPACITY;
    if (array->data == NULL)
    {
        array->data = (int *)my_malloc(sizeof(int *) * newBase);
        if (array->data)
            array->capacity = newBase;
    }
    else
    {
        void *new = realloc(array->data, newBase);
        // 重新分配内存
        if (new != NULL)
        {
            array = new;
            array->capacity = newBase;
        }
    }
}