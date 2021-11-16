#ifndef _LEXICAL_
#define _LEXICAL_
#include "lex_stack.h"
#include "nfa_Interface.h"
#include "memory_management.h"

typedef void (*fun_base)(char);
typedef int (*fun_lex)(char *, fun_base);

typedef struct WholeState
{
    enum PSW state;
} WholeState;

extern Stack *OPTR;
extern Stack *STNS;
extern WholeState *wholeStatus;
extern NfaPair *curNfa;
extern NfaPair *nfapaif;
extern Stack *nfaSet;
extern int StateNum;

extern char *initParse(char *path, fun_lex parseFun);
#endif