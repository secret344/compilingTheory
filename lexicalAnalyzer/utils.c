#include "bool.h"
#include <string.h>
#include "lexical.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
static int StateNum = 0;
// 初始化nfa节点
void setInitPair(NfaPair *n)
{
    n->startNode = (NfaNode *)malloc(sizeof(NfaNode));
    n->endNode = n->startNode->next = (NfaNode *)malloc(sizeof(NfaNode));

    n->startNode->inputset = NULL;
    n->endNode->inputset = NULL;

    n->startNode->visited = FALSE;
    n->endNode->visited = FALSE;

    n->startNode->stateNum = StateNum++;
    n->endNode->stateNum = StateNum++;

    n->startNode->anchor = 0;
    n->endNode->anchor = 0;

    n->startNode->edge = -1;
    n->endNode->edge = -1;

    n->startNode->next2 = NULL;
    n->endNode->next = NULL;
    n->endNode->next2 = NULL;
}

//语法树节点栈 "abcdzAZ19_. ";
BOOL isSTNS(char str)
{
    char s[] = "@#$abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_. ";
    return findChar(str, s);
}

//运算符栈 "+=|-[]()*?";
BOOL isOPTR(char str)
{
    char s[] = "+=|-[]()*?";
    return findChar(str, s);
}

BOOL findChar(char s, char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (s == str[i])
        {
            return TRUE;
        }
    }
    return FALSE;
}
// TODO 暂时不实现
char *ESCmatch(char s)
{
    char *result;
    switch (s)
    {
    case 'd':
        result = "0123456789";
        break;
    case 'D':
        result = "0123456789";
        break;
    case 'n':
        result = "\n";
        break;
    default:
        break;
    }
}

char *getSetLetter(char a, char b)
{
    int len = b - a + 1;
    if (len < 0)
    {
        return NULL;
    }
    char *s = malloc(len + 1);
    for (size_t i = 0; i < len; i++)
    {
        s[i] = a++;
    }
    s[len] = '\0';
    return s;
}

char *concatstr(char *target, char *source)
{
    int len = strlen(target);
    int len1 = strlen(source);
    char *s = malloc(len + len1 + 1);
    strcpy(s, target);
    strcat(s, source);
    return s;
}
/**
 * 去除字符串重复字符
*/
char *noStrRepetition(char *str)
{
    int len = strlen(str);
    char *repe = (char *)malloc(len + 1);
    int count = 0;
    for (size_t i = 0; i < len; i++)
    {
        char s = str[i];
        BOOL is = findChar(s, repe);
        if (!is)
        {
            repe[count] = s;
            count++;
        }
    }
    repe[count] = '\0';
    // 节省内存
    char *result = (char *)malloc(strlen(repe) + 1);
    strcpy(result, repe);
    free(repe);
    repe = NULL;
    return result;
}
/**
 * 取补集
*/
char *setComplement(char *str)
{
    char s[129];
    int count = 0;
    for (int i = 1; i < 128; i++)
    {
        int is = findChar(i, str);
        if (!is)
        {
            s[count++] = i;
        }
    }
    s[count] = '\0';
    char *result = (char *)malloc(strlen(s) + 1);
    strcpy(result, s);
    return result;
}

void printfNfaNode(NfaNode *n)
{
    NfaNode *a = n->next;
    NfaNode *b = n->next2;
    if (n->visited)
    {
        return;
    }
    n->visited = TRUE;
    printf("\n");
    printf("当前节点编号stateNum  %d \n", n->stateNum);
    printf("当前节点接受edge %d \n", n->edge);
    if (a)
    {
        printf("当前节点next %d  \n", a->stateNum);
    }
    if (b)
    {
        printf("当前节点next1 %d  \n", b->stateNum);
    }

    if (n->inputset)
    {
        printf("当前节点接受inputset %s %d\n", n->inputset, strlen(n->inputset));
    }
    printf("\n");
    if (a)
    {
        printfNfaNode(a);
    }
    if (b)
    {
        printfNfaNode(b);
    }
}

void printfNfa(NfaPair *n)
{
    NfaNode *a = n->startNode;
    printf("打印开始\n");
    printfNfaNode(a);
}
