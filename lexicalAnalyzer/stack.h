#include "bool.h"

#ifndef _SYMBOL_STACK_
#define _SYMBOL_STACK_

typedef struct StackNode
{
    char *data;
    struct StackNode *PStackNext;
} StackNode, *PStackNext;

typedef struct Stack
{
    PStackNext top;
    PStackNext base;
} Stack, *PStack;

PStack new_stack();

void spush(PStack PStack, char *val);
char *spop(PStack PStack);
void straversal(PStack PStack);
#endif