#ifndef _MY_ARRAY_LIST_
#define _MY_ARRAY_LIST_
#define DEFAULT_CAPACITY 10
#include <stdio.h>
#include "memory_management.h"
#include "bool.h"
#include "data_struct_utils.h"

typedef void MyArrayListNode;

typedef struct My_ArrayList
{
    int size;     // 数组大小
    int capacity; // 数组容量
    int *data;    // 数组内容
} My_ArrayList;

My_ArrayList *ArrayListCreate();
BOOL ArrayListPush(My_ArrayList *array, MyArrayListNode *node);
MyArrayListNode *ArrayListPop(My_ArrayList *array);
MyArrayListNode *ArrayListGetFormPos(My_ArrayList *array, int pos);
MyArrayListNode *ArrayListDelete(My_ArrayList *array, int pos);
void ArrayListDestroy(My_ArrayList *array);

// eq
int ArrayListFindNode(My_ArrayList *array, void *target);
BOOL ArrayListEquals(My_ArrayList *array, My_ArrayList *refArray);
BOOL ArrayListContains(My_ArrayList *array, My_ArrayList *refArray);
#endif