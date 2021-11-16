
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

extern void spush(Stack *PStack, char *val);
extern void sPointPush(Stack *PStack, void *val);
extern void *spop(Stack *PStack);
extern void straversal(Stack *PStack);
extern void sdestory(Stack *PStack, void (*fn)(void *));
extern int stacksize(Stack *PStack);
extern BOOL stackInclude(Stack *PStack, void *val);
#endif