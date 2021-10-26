#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "bool.h"
#include "stack.h"

PStack new_stack()
{
    PStack PStack;
    PStack->base = malloc(sizeof(StackNode));
    PStack->top = PStack->base;
    PStack->base->PStackNext = NULL;
    return PStack;
}

void spush(PStack PStack, char *val)
{
    PStackNext p = malloc(sizeof(StackNode));
    p->data = (char *)malloc(strlen(val) + 1);
    strcpy(p->data, val);
    p->PStackNext = PStack->top;
    PStack->top = p;
}

char *spop(PStack PStack)
{
    char *_Destination;
    if (PStack->top == PStack->base)
    {
        printf("栈为空");
        return NULL;
    };
    PStackNext p = PStack->top;
    _Destination = (char *)malloc(strlen(p->data) + 1);
    strcpy(_Destination, p->data);
    PStack->top = p->PStackNext;
    free(p->data);
    free(p);
    p = NULL;
    return _Destination;
}

void straversal(PStack PStack)
{
    if (PStack->top == PStack->base)
    {
        printf("栈为空");
        return;
    };
    printf("栈内数据:\n");
    while (PStack->top != PStack->base)
    {
        PStackNext p = PStack->top;
        printf("%s ", p->data);
        PStack->top = p->PStackNext;
    }
    printf("\n");
    printf("遍历结束\n");
}