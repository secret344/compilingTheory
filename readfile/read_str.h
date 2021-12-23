#ifndef _READ_STR_
#define _READ_STR_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_management.h"
#include "bool.h"

typedef char (*fun_rf)(void *);

typedef struct Read_Str_Instance
{
    const char *buff;  // 缓冲区 保存所有读取的字符
    unsigned int size; // 缓冲区大小
    int row;           // 行号
    int col;           // 当前列号
    unsigned int next; // 指向当前要读入的字符位置
    BOOL isEnd;
    fun_rf advance;
} Read_Str;

Read_Str *newReadStr(const char *str);

#endif