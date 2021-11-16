#include "stns_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "nfa_parse.h"

static NfaPair *stnspaif = NULL;
void stnsInitfun(char str)
{
    if (wholeStatus->state == PSWdef)
    {
        wholeStatus->state = PSWsinglechar;
    }
    stnspaif = (NfaPair *)my_malloc(sizeof(NfaPair));
    setInitPair(stnspaif);
    curNfa = stnspaif;
}
// . 代表除去回车换行符
void stnsDotfun()
{
    stnspaif->startNode->inputset = "\n\r";
    stnspaif->startNode->anchor = 1;
    char *s = setComplement(stnspaif->startNode->inputset);
    stnspaif->startNode->inputset = s;
    stnsDeffun(-2);
}

void stnsDeffun(char str)
{
    stnspaif->startNode->edge = str;
    wholeStatus->state = PSWdef;
}
