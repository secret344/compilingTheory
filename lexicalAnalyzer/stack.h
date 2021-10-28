#include "bool.h"

#ifndef _SYMBOL_STACK_
#define _SYMBOL_STACK_
typedef union StackData
{
    int n;
    char *s;
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

void spush(Stack *PStack, char *val);
char *spop(Stack *PStack);
void straversal(Stack *PStack);
void sdestory(Stack *PStack);
int stacksize(Stack *PStack);
#endif