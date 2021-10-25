#include "bool.h"

#ifndef _SYMBOL_STACK_
#define _SYMBOL_STACK_

typedef char StackNodeSymbol[5];

typedef struct StackNode
{
    StackNodeSymbol data;
    struct StackNode *PStackNext;
} StackNode, *PStackNext;

typedef struct Stack
{
    PStackNext top;
    PStackNext base;
} Stack, *PStack;

void new_stack();

void push(PStack PStack, StackNodeSymbol val);
BOOL pop(PStack PStack, StackNodeSymbol _Destination);
#endif