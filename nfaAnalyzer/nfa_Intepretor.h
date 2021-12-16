
#ifndef _NFA_INTEPRETOR_
#define _NFA_INTEPRETOR_
#include "lex_stack.h"
#include "nfa_Interface.h"

typedef union
{
    BOOL lastAccepted;
    int num;
} MatchBackType;

void initpretNfa(NfaNode *start, char *str, MatchBackType *mt);
void initMatchNfa(char *str);
Stack *e_closure(Stack *next);
Stack *e_move(Stack *next, char c);
#endif