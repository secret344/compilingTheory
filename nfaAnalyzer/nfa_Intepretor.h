
#ifndef _NFA_INTEPRETOR_
#define _NFA_INTEPRETOR_
#include "lex_stack.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define IsExists(a, b, c) ((a) ? (b) : (c))

typedef union
{
    BOOL lastAccepted;
    int num;
} MatchBackType;

extern void initpretNfa(NfaNode *start, char *str, MatchBackType *mt);
extern void initMatchNfa(char *str);
extern Stack *e_closure(Stack *next);
extern Stack *move(Stack *next, char c);
#endif