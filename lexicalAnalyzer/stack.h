#include "nfa_Interface.h"

#ifndef _SYMBOL_STACK_
#define _SYMBOL_STACK_

typedef union StackData
{
    int n;
    char *s;
    void *nfa;
} StackData;

typedef struct StackNode
{
    StackData data;
    struct StackNode *PStackNext;
} StackNode;

typedef struct Stack
{
    StackNode *top;
    StackNode *base;
} Stack;

Stack *new_stack();

extern void spush(Stack *PStack, char *val);
extern void sOptrPush(Stack *PStack, void *val);
extern char *spop(Stack *PStack);
extern void *sOptrPop(Stack *PStack);
extern void straversal(Stack *PStack);
extern void sdestory(Stack *PStack);
extern int stacksize(Stack *PStack);
extern BOOL stackInclude(Stack *PStack, void *val);
#endif