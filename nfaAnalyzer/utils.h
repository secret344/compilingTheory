
#ifndef _UTILS_
#define _UTILS_
#include "nfa_Interface.h"
extern BOOL isSTNS(char str);
extern BOOL isOPTR(char str);
extern BOOL findChar(char s, char str[]);
extern char *ESCmatch(char s);
extern char *getSetLetter(char a, char b);
extern char *concatstr(char *target, char *source);
extern char *noStrRepetition(char *str);
extern char *setComplement(char *str);
extern void printfNfa(NfaPair *n);
extern void setInitPair(NfaPair *n);
#endif