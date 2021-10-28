#include "lexical.h"
#include "setutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static void checkSetStack();
static Stack *setStack = NULL;
static BOOL isInit = FALSE;
void setInitfun()
{
    wholeStatus->state = PSWset;
    nfapaif->startNode->edge = -2;
    nfapaif->startNode->visited = FALSE;
    nfapaif->startNode->inputset = NULL;
    setStack = new_stack();
}

void setNOTfun()
{
    if (isInit)
    {
        // 暂时忽略不在开头的^字符
        printf("^字符 必须在开头使用");
        return;
    }
    else
    {

        nfapaif->startNode->anchor = 1;
    }
}

void setStartfun()
{
    wholeStatus->state = PSWsetStart;
}

void setMainfun(char *s)
{

    isInit = TRUE;
    switch (wholeStatus->state)
    {
    case PSWsetStart:
        // 65 A  97 a
        // 90 Z 122 z
        // 填充inputset
        printf("");
        char *prev = spop(setStack);
        if (!prev)
        {
            printf(" - 前必须有字符,行:%d,列:%d\n", row, col);
        }
        else
        {
            char *inputset = getSetLetter(*prev, *s);
            if (!inputset)
            {
                printf("集合内元素顺序错误,a-z 或者 A-Z,行:%d,列:%d\n", row, col);
            }
            else
            {
                if (!nfapaif->startNode->inputset)
                {
                    nfapaif->startNode->inputset = inputset;
                }
                else
                {
                    // 合并
                    char *str = concatstr(nfapaif->startNode->inputset, inputset);
                    free(nfapaif->startNode->inputset);
                    nfapaif->startNode->inputset = str;
                }
            }
        }
        free(prev);
        prev = NULL;
        wholeStatus->state = PSWset;
        break;
    default:
        spush(setStack, s);
        break;
    }
}

void setEndfun()
{
    int len = stacksize(setStack);
    if (len)
    {
        checkSetStack();
    }
    // 释放集合栈
    sdestory(setStack);
    setStack = NULL;
    wholeStatus->state = PSWdef;
    isInit = FALSE;
    // 此时需要检查是否含有 ^
    printf("结束打印%s", nfapaif->startNode->inputset);
}
void checkSetStack()
{
    int len = stacksize(setStack);
    int len1 = strlen(nfapaif->startNode->inputset);
    char *str = malloc(len + len1 + 1);
    strcpy(str, nfapaif->startNode->inputset);

    int count = 0;
    // 结束检查集合栈内字符
    while (setStack->base != setStack->top)
    {
        char *s = spop(setStack);
        BOOL is = findChar(*s, str);
        if (!is)
        {
            str[len1 + count] = *s;
            count++;
        }
        free(s);
        s = NULL;
    }
    str[len1 + count] = '\0';
    // 去除重复的字符串
    char *result = malloc(strlen(str) + 1);
    strcpy(result, str);
    free(str);
    str = NULL;
    if (len1)
    {
        free(nfapaif->startNode->inputset);
    }
    nfapaif->startNode->inputset = result;
}
// TODO 转义字符
void setESCfun()
{

    wholeStatus->state = PSWsetESC;
}
