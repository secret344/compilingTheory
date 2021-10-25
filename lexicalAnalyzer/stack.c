#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "bool.h"
#include "stack.h"

void new_stack(PStack PStack)
{
    PStack->base = malloc(sizeof(StackNode));
    PStack->top = PStack->base;
    PStack->base->PStackNext = NULL;
}

void push(PStack PStack, StackNodeSymbol val)
{
    PStackNext p = malloc(sizeof(StackNode));
    strcpy(p->data, val);
    p->PStackNext = PStack->top;
    PStack->top = p;
}

BOOL pop(PStack PStack, StackNodeSymbol _Destination)
{
    if (PStack->top == PStack->base)
    {
        printf("栈为空");
        return FALSE;
    };
    PStackNext p = PStack->top;
    strcpy(_Destination, p->data);
    PStack->top = p->PStackNext;
    free(p->data);
    free(p);
    p = NULL;
    return TRUE;
}