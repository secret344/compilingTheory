
#ifndef _NFA_INTEPRETOR_
#define _NFA_INTEPRETOR_
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define IsExists(a, b, c) ((a) ? (b) : (c))

typedef union
{
    BOOL lastAccepted;
    int num;
} MatchBackType;

extern void initpretNfa(NfaNode *start, char *str, MatchBackType *mt);
extern void initMatchNfa(Stack *start, char *str);
#endif