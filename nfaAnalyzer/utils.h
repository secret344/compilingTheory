
#ifndef _UTILS_
#define _UTILS_
#include "nfa_Interface.h"
#include "lex_stack.h"
#include "cJSON.h"

BOOL isSTNS(char str);
BOOL isOPTR(char str);
BOOL findChar(char s, char str[]);
char *ESCmatch(char s);
char *getSetLetter(char a, char b);
char *concatstr(char *target, char *source);
char *noStrRepetition(char *str);
char *setComplement(char *str);
void printfNfa(NfaPair *n);
void setInitPair(NfaPair *n);
void JsonNfaParse(NfaNode *n, cJSON *parentNode, char *childName);
#endif