
#ifndef _SYMBOL_STACK_
#define _SYMBOL_STACK_
#include "bool.h"
#include "memory_management.h"
typedef union StackData
{
    int n;
    void *p;
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
void sPointPush(Stack *PStack, void *val);
void *spop(Stack *PStack);
void straversal(Stack *PStack);
void sdestory(Stack *PStack, void (*fn)(void *));
int stacksize(Stack *PStack);
BOOL stackPointerInclude(Stack *PStack, void *val);
void *speek(Stack *PStack);
#endif