#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "bool.h"
#include "stack.h"

Stack *new_stack()
{
    Stack *PStack = (Stack *)malloc(sizeof(Stack));
    PStack->base = (StackNode *)malloc(sizeof(StackNode));
    PStack->top = PStack->base;
    PStack->base->PStackNext = NULL;
    PStack->base->data = NULL;
    return PStack;
}

void spush(Stack *PStack, char *val)
{
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->data = (char *)malloc(strlen(val) + 1);
    strcpy(p->data, val);
    p->PStackNext = PStack->top;
    PStack->top = p;
}

char *spop(Stack *PStack)
{
    if (PStack->top == PStack->base)
    {
        printf("栈为空\n");
        return NULL;
    };

    StackNode *p = PStack->top;
    char *_Destination = (char *)malloc(strlen(p->data) + 1);
    strcpy(_Destination, p->data);
    PStack->top = p->PStackNext;
    free(p->data);
    p->data = NULL;
    free(p);
    p = NULL;
    return _Destination;
}

void straversal(Stack *PStack)
{
    if (PStack->top == PStack->base)
    {
        printf("栈为空\n");
    }
    else
    {
        printf("栈内数据:\n");
    };

    StackNode *temp = PStack->top;
    while (PStack->top != PStack->base)
    {
        StackNode *p = PStack->top;
        printf("%s ", p->data);
        PStack->top = p->PStackNext;
    }
    printf("\n");
    printf("遍历结束\n");
    PStack->top = temp;
}

void sdestory(Stack *PStack)
{
    char *s;
    while (s = spop(PStack))
    {
        free(s);
        s = NULL;
    }
    PStack->top = NULL;
    free(PStack->base);
    PStack->base = NULL;
    free(PStack);
    PStack = NULL;
    printf("释放完成\n");
}