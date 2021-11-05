#include <stdio.h>
#include "stack.h"
Stack *e_closure(Stack *next);
void initpretNfa(NfaNode *start)
{
    printf("开始匹配");
    Stack *next = new_stack();
    sOptrPush(next, start);
    // 查找closure
}

Stack *e_closure(Stack *next)
{
    // 查找所有next栈中的closure
    Stack *nfaStack = new_stack();
    while (stacksize(next))
    {
        NfaNode *node = sOptrPop(next);
        sOptrPush(nfaStack, node);
    }

    while (stacksize(nfaStack))
    {
        NfaNode *node = sOptrPop(nfaStack);
        // 检查节点 next next2
        // 需要去重
        if (node->next && node->edge == -1)
        {
            /* code */
        }

        if (node->next2 && node->edge == -1)
        {
            /* code */
        }
    }
    return next;
}