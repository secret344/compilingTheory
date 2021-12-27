
#ifndef _UTILS_
#define _UTILS_
#include "nfa_Interface.h"
#include "lex_stack.h"
#include "cJSON.h"

BOOL isSTNS(char str);
BOOL isOPTR(char str);
char *ESCmatch(char s);
void printfNfa(NfaPair *n);
void setInitPair(NfaPair *n);
void JsonNfaParse(NfaNode *n, cJSON *parentNode, char *childName);
#endif