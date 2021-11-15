#include <stdio.h>
#include "lex_stack.h"
#include "nfa_Interface.h"
#include "utils.h"
#include "nfa_Intepretor.h"
#include <string.h>
#include "nfa_parse.h"

static Stack *e_closure(Stack *next);
static Stack *move(Stack *next, char c);
static BOOL hasAcceptState(Stack *next);
static int count = 0;

void initMatchNfa(char *str)
{
    if (stacksize(nfaSet) <= 0)
    {
        return;
    }

    count = 0;
    Stack *prev = new_stack();
    MatchBackType ResultMt[2] = {FALSE, 0};
    int len = strlen(str);
    while (count < len)
    {

        NfaPair *n = sPointPop(nfaSet);
        sPointPush(prev, n);
        MatchBackType mtt[2];
        initpretNfa(n->startNode, str, mtt);
        if (mtt[0].lastAccepted)
        {
            ResultMt[0].lastAccepted = TRUE;
            // 贪婪匹配
            ResultMt[1].num = MAX(mtt[1].num, ResultMt[1].num);
            printf("匹配完成，匹配正则名称为:%s;匹配开始位置:%d;匹配结尾位置为%d\n", n->endNode->name, count, mtt[1].num);
        }

        if (!stacksize(nfaSet))
        {
            printf("一轮匹配结束\n");
            sdestory(nfaSet);
            nfaSet = prev;
            prev = new_stack();
            if (!ResultMt[0].lastAccepted)
            {
                printf("匹配失败,发现未知字符，尝试跳过一位。\n");
                count++;
            }
            else
            {
                printf("匹配成功,继续进行后续匹配,%d\n", ResultMt[1].num);
                count = ResultMt[1].num;
                ResultMt[0].lastAccepted = FALSE;
            }
        }
    }
}

void initpretNfa(NfaNode *start, char *str, MatchBackType *mt)
{
    Stack *next = new_stack();
    sPointPush(next, start);
    // 查找closure
    next = e_closure(next);
    BOOL lastAccepted = FALSE;
    size_t i;
    int len = strlen(str);
    for (i = count; i < len; i++)
    {
        char c = str[i];
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
        printf("正在匹配字符为：%c \n", c);
    }
    mt[0].lastAccepted = lastAccepted;
    mt[1].num = i;
}

Stack *e_closure(Stack *next)
{
    Stack *nextStack = new_stack();
    // 查找所有next栈中的closure
    Stack *nfaStack = new_stack();
    while (stacksize(next))
    {
        NfaNode *node = sPointPop(next);
        sPointPush(nextStack, node);
        sPointPush(nfaStack, node);
    }
    sdestory(next);
    while (stacksize(nfaStack))
    {
        NfaNode *node = sPointPop(nfaStack);
        // 检查节点 next next2
        // 需要去重
        if (node->next && node->edge == -1)
        {
            if (stackInclude(nextStack, node->next) == FALSE)
            {
                sPointPush(nextStack, node->next);
                sPointPush(nfaStack, node->next);
            }
        }

        if (node->next2 && node->edge == -1)
        {
            if (stackInclude(nextStack, node->next2) == FALSE)
            {
                sPointPush(nextStack, node->next2);
                sPointPush(nfaStack, node->next2);
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
        NfaNode *n = sPointPop(next);
        char *s = n->inputset;
        int edge = n->edge;

        if (edge == c || (edge == -2 && findChar(c, s)))
        {
            sPointPush(result, n->next);
        }
    }
    sdestory(next);
    return result;
}

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
