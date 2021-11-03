#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "bool.h"
#include "stack.h"
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
    p->data.s = (char *)malloc(strlen(val) + 1);
    strcpy(p->data.s, val);
    p->PStackNext = PStack->top;
    PStack->top = p;
    PStack->base->data.n = PStack->base->data.n + 1;
}

void sOptrPush(Stack *PStack, NfaPair *val)
{
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->data.nfa = val;
    p->PStackNext = PStack->top;
    PStack->top = p;
    PStack->base->data.n = PStack->base->data.n + 1;
}

char *spop(Stack *PStack)
{
    if (PStack->top == PStack->base)
    {
        printf("栈为空\n");
        return NULL;
    };

    StackNode *p = PStack->top;
    char *_Destination = (char *)malloc(strlen(p->data.s) + 1);
    strcpy(_Destination, p->data.s);
    PStack->top = p->PStackNext;
    free(p->data.s);
    p->data.s = NULL;
    free(p);
    p = NULL;
    PStack->base->data.n = PStack->base->data.n - 1;
    return _Destination;
}

NfaPair *sOptrPop(Stack *PStack)
{
    if (PStack->top == PStack->base)
    {
        printf("栈为空\n");
        return NULL;
    };

    StackNode *p = PStack->top;
    NfaPair *_Destination = p->data.nfa;
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

int stacksize(Stack *PStack)
{
    return PStack->base->data.n;
}