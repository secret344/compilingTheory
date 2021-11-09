#ifndef _LEXICAL_
#define _LEXICAL_
#include "../datastructure/stack.h"
#include "nfa_Interface.h"

typedef struct WholeState
{
    enum PSW state;
} WholeState;

extern Stack *OPTR;
extern Stack *STNS;
extern WholeState *wholeStatus;
extern NfaPair *curNfa;
extern NfaPair *nfapaif;
extern int initParse(char *path);
extern Stack *nfaSet;
#endif