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
void switchOptr(char *s)
{
    wholeStatus->state = PSWoptr;
    optrpaif = (NfaPair *)malloc(sizeof(NfaPair));
    switch (*s)
    {
    case '*':
    case '+':
    case '?':
        optrpaif->startNode = (NfaNode *)malloc(sizeof(NfaNode));
        optrpaif->endNode->next = (NfaNode *)malloc(sizeof(NfaNode));
        StarClosure(*s);
        PlusClosure(*s);
        OptionsClosure(*s);
        break;
    default:
        break;
    }
    wholeStatus->state = PSWdef;
}
