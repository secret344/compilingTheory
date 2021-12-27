#include <string.h>
#include "nfa_parse.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

// 初始化nfa节点
void setInitPair(NfaPair *n)
{
    n->startNode = (NfaNode *)my_malloc(sizeof(NfaNode));
    n->endNode = n->startNode->next = (NfaNode *)my_malloc(sizeof(NfaNode));

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

//语法树节点栈 <>!@#=$abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.:\";
BOOL isSTNS(char str)
{
    char s[] = "<>!@&#=$abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.:\"";
    return findChar(str, s);
}

//正则运算符栈 "+=|-[]()*?";
BOOL isOPTR(char str)
{
    char s[] = "+|-[]()*?";
    return findChar(str, s);
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
    return result;
}

void printfNfaNode(NfaNode *n, BOOL isPrintf)
{
    NfaNode *a = n->next;
    NfaNode *b = n->next2;
    if (n->visited)
    {
        return;
    }
    n->visited = TRUE;

    if (isPrintf)
    {
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
            printf("当前节点接受inputset %s ;inputset length： %d\n", n->inputset, strlen(n->inputset));
        }
        printf("\n");
    }

    if (a)
    {
        printfNfaNode(a, isPrintf);
    }
    if (b)
    {
        printfNfaNode(b, isPrintf);
    }
}

void printfNfa(NfaPair *n)
{
    NfaNode *a = n->startNode;
    printf("打印开始\n");
    printfNfaNode(a, TRUE);
}

void JsonNfaParse(NfaNode *n, cJSON *parentNode, char *childName)
{

    NfaNode *a = n->next;
    NfaNode *b = n->next2;
    cJSON *current = cJSON_CreateObject();

    cJSON *stateNum = cJSON_CreateNumber(n->stateNum);
    cJSON *edge = cJSON_CreateNumber(n->edge);
    cJSON *inputset = cJSON_CreateString(n->inputset);

    cJSON_AddItemToObject(current, "stateNum", stateNum);
    cJSON_AddItemToObject(current, "edge", edge);
    cJSON_AddItemToObject(current, "inputset", inputset);
    cJSON_AddItemToObject(parentNode, childName, current);

    if (n->visited)
    {
        return;
    }
    n->visited = TRUE;

    if (a)
    {
        JsonNfaParse(a, current, "next1");
    }
    if (b)
    {
        JsonNfaParse(b, current, "next2");
    }
}
