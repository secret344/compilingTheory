#include "lexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static NfaPair *optrpaif = NULL;

void StarClosure(char s)
{
    if (s != '*')
    {
        return;
    }

    optrpaif->startNode->next = curNfa->startNode;

    optrpaif->startNode->next2 = optrpaif->endNode;

    curNfa->endNode->next = optrpaif->endNode;

    curNfa->endNode->next2 = optrpaif->startNode;

    // 链接完成更新当前NODE
    curNfa->startNode = optrpaif->startNode;
    curNfa->endNode = optrpaif->endNode;
}

void PlusClosure(char s)
{
    if (s != '+')
    {
        return;
    }

    optrpaif->startNode->next = curNfa->startNode;

    curNfa->endNode->next = optrpaif->endNode;

    curNfa->endNode->next2 = optrpaif->startNode;

    // 链接完成更新当前NODE
    curNfa->startNode = optrpaif->startNode;
    curNfa->endNode = optrpaif->endNode;
}

void OptionsClosure(char s)
{
    if (s != '?')
    {
        return;
    }

    optrpaif->startNode->next = curNfa->startNode;

    curNfa->endNode->next = optrpaif->endNode;

    optrpaif->startNode->next2 = optrpaif->endNode;

    // 链接完成更新当前NODE
    curNfa->startNode = optrpaif->startNode;
    curNfa->endNode = optrpaif->endNode;
}

void orDispose(char *s)
{
    optrpaif = curNfa; // 保存当前nfa节点，等待下次节点执行或运算
    curNfa = NULL;
    spush(OPTR, s);
}

void bracketDispose(char *s)
{
    if (*s == '(')
    {
        optrpaif = (NfaPair *)malloc(sizeof(NfaPair));
        setInitPair(optrpaif);
        nfapaif = optrpaif; // 括号生成新的树 碰到) 组合

        spush(OPTR, s);
        return;
    }
}

void switchOptr(char *s)
{

    switch (*s)
    {
    case '*':
    case '+':
    case '?':
        wholeStatus->state = PSWoptr;
        optrpaif = (NfaPair *)malloc(sizeof(NfaPair));
        setInitPair(optrpaif);
        StarClosure(*s);
        PlusClosure(*s);
        OptionsClosure(*s);
        wholeStatus->state = PSWdef;
        break;
    case '|':
        orDispose(s);
        break;
    case '(':
    case ')':
        bracketDispose(s);
        break;
    default:
        break;
    }
}
