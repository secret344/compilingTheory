#include "nfa_parse.h"
#include "set_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "read_file.h"

static void checkSetStack();
static Stack *setStack = NULL;
static BOOL isInit = FALSE;
static NfaPair *setpaif = NULL;

void setInitfun()
{
    setStack = new_stack();
    wholeStatus->state = PSWset;

    setpaif = (NfaPair *)malloc(sizeof(NfaPair));
    setInitPair(setpaif);
    setpaif->startNode->edge = -2;
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
        setpaif->startNode->anchor = 1;
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
                if (!setpaif->startNode->inputset)
                {
                    setpaif->startNode->inputset = inputset;
                }
                else
                {
                    // 合并
                    char *str = concatstr(setpaif->startNode->inputset, inputset);
                    free(setpaif->startNode->inputset);
                    setpaif->startNode->inputset = str;
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
void setEndCheck()
{
    char *s = setpaif->startNode->inputset;
    if (setpaif->startNode->anchor == 1)
    {
        s = setComplement(setpaif->startNode->inputset);
        free(setpaif->startNode->inputset);
    }
    char *result = noStrRepetition(s);
    free(s);
    s = NULL;
    setpaif->startNode->inputset = result;
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
    setEndCheck();
    curNfa = setpaif;
}
void checkSetStack()
{
    int len = stacksize(setStack);
    int len1 = 0;
    if (setpaif->startNode->inputset)
    {
        len1 = strlen(setpaif->startNode->inputset);
    }
    char *str = malloc(len + len1 + 1);
    // 去除重复的字符串
    if (len1)
    {
        strcpy(str, setpaif->startNode->inputset);
        free(setpaif->startNode->inputset);
    }
    int count = 0;
    // 结束检查集合栈内字符
    while (setStack->base != setStack->top)
    {
        char *s = spop(setStack);
        BOOL is = findChar(*s, str);
        str[len1 + count] = *s;
        count++;
        free(s);
        s = NULL;
    }
    str[len1 + count] = '\0';
    setpaif->startNode->inputset = str;
}
// TODO 转义字符
void setESCfun()
{

    wholeStatus->state = PSWsetESC;
}
