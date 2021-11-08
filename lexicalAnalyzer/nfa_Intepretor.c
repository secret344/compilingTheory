#include <stdio.h>
#include "stack.h"
#include "utils.h"

Stack *e_closure(Stack *next);
Stack *move(Stack *next, char c);
BOOL hasAcceptState(Stack *next)
{
    BOOL res = FALSE;
    if (next == NULL || !stacksize(next))
    {
        return FALSE;
    }

    StackNode *temp = next->top;
    while (next->top != next->base)
    {
        StackNode *p = next->top;
        NfaNode *n = p->data.nfa;
        if (n->next == NULL && n->next2 == NULL)
        {
            res = TRUE;
        }
        next->top = p->PStackNext;
    }
    next->top = temp;

    return res;
}

void initpretNfa(NfaNode *start, char *str)
{
    printf("开始匹配");
    Stack *next = new_stack();
    sOptrPush(next, start);
    // 查找closure
    next = e_closure(next);
    BOOL lastAccepted = FALSE;
    char s[100];
    int count = 0;
    while (*str != '\0')
    {
        char c = *str++;
        next = move(next, c);
        next = e_closure(next);
        if (stacksize(next))
        {
            if (hasAcceptState(next))
            {
                lastAccepted = TRUE;
            }
        }
        else
        {
            break;
        }
        s[count++] = c;
    }

    if (lastAccepted)
    {
        s[count] = '\0';
        printf("匹配完成，匹配字符串为 %s\n", s);
    }
}

Stack *e_closure(Stack *next)
{
    Stack *nextStack = new_stack();
    // 查找所有next栈中的closure
    Stack *nfaStack = new_stack();
    while (stacksize(next))
    {
        NfaNode *node = sOptrPop(next);
        sOptrPush(nextStack, node);
        sOptrPush(nfaStack, node);
    }
    sdestory(next);
    while (stacksize(nfaStack))
    {
        NfaNode *node = sOptrPop(nfaStack);
        // 检查节点 next next2
        // 需要去重
        if (node->next && node->edge == -1)
        {
            if (stackInclude(nextStack, node->next) == FALSE)
            {
                sOptrPush(nextStack, node->next);
                sOptrPush(nfaStack, node->next);
            }
        }

        if (node->next2 && node->edge == -1)
        {
            if (stackInclude(nextStack, node->next2) == FALSE)
            {
                sOptrPush(nextStack, node->next2);
                sOptrPush(nfaStack, node->next2);
            }
        }
    }
    sdestory(nfaStack);
    return nextStack;
}

Stack *move(Stack *next, char c)
{
    Stack *result = new_stack();
    while (stacksize(next))
    {
        NfaNode *n = sOptrPop(next);
        char *s = n->inputset;
        int edge = n->edge;

        if (edge == c || (edge == -2 && findChar(c, s)))
        {
            sOptrPush(result, n->next);
        }
    }
    sdestory(next);
    return result;
}