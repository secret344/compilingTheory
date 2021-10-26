#include "bool.h"

#ifndef _SYMBOL_STACK_
#define _SYMBOL_STACK_

typedef struct StackNode
{
    char *data;
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
#endif