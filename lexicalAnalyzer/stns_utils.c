#include "stns_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static NfaPair *stnspaif = NULL;
void stnsInitfun(char str)
{
    if (wholeStatus->state == PSWdef)
    {
        wholeStatus->state = PSWsinglechar;
    }
    stnspaif = (NfaPair *)malloc(sizeof(NfaPair));

    nfapaif->startNode = stnspaif->startNode = (NfaNode *)malloc(sizeof(NfaNode));
    nfapaif->endNode = nfapaif->startNode->next = (NfaNode *)malloc(sizeof(NfaNode));

    stnspaif->startNode->visited = FALSE;
    stnspaif->startNode->inputset = NULL;
}
// . 代表除去回车换行符
void stnsDotfun()
{
    if (wholeStatus->state == PSWESC)
    {
        stnsDeffun('.');
        return;
    }
    stnspaif->startNode->inputset = "\n\r";
    stnsDeffun(-2);
}

void stnsDeffun(char str)
{
    stnspaif->startNode->edge = str;
    wholeStatus->state == PSWdef;
}