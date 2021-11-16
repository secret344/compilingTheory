#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex_stack.h"
#include "nfa_Interface.h"

Stack *new_stack()
{
    Stack *PStack = (Stack *)malloc(sizeof(Stack));
    PStack->base = (StackNode *)malloc(sizeof(StackNode));

    PStack->top = PStack->base;
    PStack->base->PStackNext = NULL;
    PStack->base->data.n = 0;
    return PStack;
}

void spush(Stack *PStack, char *val)
{
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    char *str = (char *)malloc(strlen(val) + 1);
    strcpy(str, val);
    p->data.p = str;
    p->PStackNext = PStack->top;
    PStack->top = p;
    PStack->base->data.n = PStack->base->data.n + 1;
}

void sPointPush(Stack *PStack, void *val)
{
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->data.p = val;
    p->PStackNext = PStack->top;
    PStack->top = p;
    PStack->base->data.n = PStack->base->data.n + 1;
}

void *spop(Stack *PStack)
{
    if (PStack->top == PStack->base)
    {
        return NULL;
    };

    StackNode *p = PStack->top;
    void *_Destination = p->data.p;
    PStack->top = p->PStackNext;
    free(p);
    p = NULL;
    PStack->base->data.n = PStack->base->data.n - 1;
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
        printf("%s ", p->data.p);
        PStack->top = p->PStackNext;
    }
    printf("\n");
    printf("遍历结束\n");
    PStack->top = temp;
}

void sdestory(Stack *PStack, void (*fn)(void *))
{
    while (stacksize(PStack))
    {
        void *s = spop(PStack);
        if (fn)
        {
            fn(s);
        }
        else
        {
            free(s);
            s = NULL;
        }
    }
    PStack->top = NULL;
    free(PStack->base);
    PStack->base = NULL;
    free(PStack);
    PStack = NULL;
}

int stacksize(Stack *PStack)
{
    return PStack->base->data.n;
}

BOOL stackInclude(Stack *PStack, void *val)
{
    BOOL bool = FALSE;
    if (PStack->top == PStack->base)
    {
        return FALSE;
    }
    else
    {
        StackNode *temp = PStack->top;
        while (PStack->top != PStack->base)
        {
            StackNode *p = PStack->top;
            if (p->data.p == val)
            {
                bool = TRUE;
            }
            PStack->top = p->PStackNext;
        }
        PStack->top = temp;
    }
    return bool;
}