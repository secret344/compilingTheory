#include "bool.h"
#ifndef _UTILS_
#define _UTILS_
extern BOOL isSTNS(char str);
extern BOOL isOPTR(char str);
extern BOOL findChar(char s, char str[]);
extern char *ESCmatch(char s);
extern char *getSetLetter(char a, char b);
extern char *concatstr(char *target, char *source);
extern char *noStrRepetition(char *str);
extern char *setComplement(char *str);
#endif