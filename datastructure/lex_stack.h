
#ifndef _SYMBOL_STACK_
#define _SYMBOL_STACK_
#include "bool.h"
#include "memory_management.h"
#include "my_iterator.h"
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

typedef struct Stack_Iter_Inner
{
    StackNode *item;
} Stack_Iter_Inner, *stack_iter_inner;

Stack *new_stack();

void spush(Stack *PStack, char *val);
void sPointPush(Stack *PStack, void *val);
void sIntPush(Stack *PStack, int val);
void *spop(Stack *PStack);
void straversal(Stack *PStack);
void sdestory(Stack *PStack, void (*fn)(void *));
int stacksize(Stack *PStack);
BOOL stackPointerInclude(Stack *PStack, void *val);
void *speek(Stack *PStack);

My_Iterator *newStackIterator(Stack *PStack);
BOOL StackContainsAll(Stack *source, Stack *target);
#endif