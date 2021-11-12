#ifndef _LEXICAL_
#define _LEXICAL_
#include "../datastructure/stack.h"
#include "nfa_Interface.h"
typedef void (*fun_base)(char);
typedef int (*fun_lex)(char*, fun_base);

typedef struct WholeState
{
    enum PSW state;
} WholeState;

extern Stack *OPTR;
extern Stack *STNS;
extern WholeState *wholeStatus;
extern NfaPair *curNfa;
extern NfaPair *nfapaif;
extern int initParse(char *path, fun_lex parseFun);
extern Stack *nfaSet;
#endif