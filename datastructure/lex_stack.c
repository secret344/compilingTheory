#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex_stack.h"
#include "nfa_Interface.h"

Stack *new_stack()
{
    Stack *PStack = (Stack *)my_malloc(sizeof(Stack));
    PStack->base = (StackNode *)my_malloc(sizeof(StackNode));

    PStack->top = PStack->base;
    PStack->base->PStackNext = NULL;
    PStack->base->data.n = 0;
    return PStack;
}

void spush(Stack *PStack, char *val)
{
    StackNode *p = (StackNode *)my_malloc(sizeof(StackNode));
    char *str = (char *)my_malloc(strlen(val) + 1);
    strcpy(str, val);
    p->data.p = str;
    p->PStackNext = PStack->top;
    PStack->top = p;
    PStack->base->data.n = PStack->base->data.n + 1;
}

void sPointPush(Stack *PStack, void *val)
{
    StackNode *p = (StackNode *)my_malloc(sizeof(StackNode));
    p->data.p = val;
    p->PStackNext = PStack->top;
    PStack->top = p;
    PStack->base->data.n = PStack->base->data.n + 1;
}

void sIntPush(Stack *PStack, int val)
{
    StackNode *p = (StackNode *)my_malloc(sizeof(StackNode));
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

    my_free(p);
    p = NULL;

    PStack->base->data.n = PStack->base->data.n - 1;
    return _Destination;
}
// 查看栈顶 不释放
void *speek(Stack *PStack)
{
    if (PStack->top == PStack->base)
    {
        return NULL;
    };
    return PStack->top->data.p;
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
        printf("%d ", p->data.n);
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
        if (fn != NULL)
        {
            fn(s);
        }
        else
        {
            my_free(s);
            s = NULL;
        }
    }
    PStack->top = NULL;
    my_free(PStack->base);
    PStack->base = NULL;
    my_free(PStack);
    PStack = NULL;
}

int stacksize(Stack *PStack)
{
    return PStack->base->data.n;
}

BOOL stackPointerInclude(Stack *PStack, void *val)
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
                break;
            }
            PStack->top = p->PStackNext;
        }
        PStack->top = temp;
    }
    return bool;
}

static void *stack_get_next(Stack *PStack, stack_iter_inner iter_inner)
{
    stack_iter_inner p = iter_inner;
    void *n = p->item->data.p;
    p->item = p->item->PStackNext;
    return n;
}

static BOOL stack_has_next(Stack *PStack, stack_iter_inner iter_inner)
{
    if (iter_inner->item == PStack->base)
    {
        return FALSE;
    };
    return TRUE;
}
/**
 * @brief 只能返回指针 也就是data.p
 * 具体信息查看源码
 * 个人使用，未做优化，未做调整。
 * @param PStack 
 * @return My_Iterator* 
 */
My_Iterator *newStackIterator(Stack *PStack)
{
    if (PStack == NULL)
    {
        return NULL;
    }

    stack_iter_inner p = NULL;
    p = my_malloc(sizeof(p));
    if (!p)
        return NULL;
    p->item = PStack->top;
    return my_iterator_new(PStack, p, (GET_NEXT_HOOK_FUNC)stack_get_next, (HAS_NEXT_HOOK_FUNC)stack_has_next);
}
/**
 * @brief 判断集合source是否包含集合target全部数据
 * 若target = NULL 返回 TRUE
 * @param source 
 * @param target 
 * @return BOOL 
 */
BOOL StackContainsAll(Stack *source, Stack *target)
{
    My_Iterator *itor = newStackIterator(target);
    while (has_itor_next(itor))
    {
        void *p = get_itor_next(itor);
        if (stackPointerInclude(source, p) == FALSE)
        {
            return FALSE;
        }
    }
    my_iterator_free(itor);
    return TRUE;
}

/**
 * @brief 栈反转
 * 返回一个翻转后新的栈 不会影响旧的栈
 * @param point 
 * @return Stack* 
 */
Stack *StackReversal(Stack *point)
{
    Stack *newStack = new_stack();
    My_Iterator *itor = newStackIterator(point);
    while (has_itor_next(itor))
    {
        void *p = get_itor_next(itor);
        sPointPush(newStack, p);
    }
    my_iterator_free(itor);
    return newStack;
}

static StackNode *reversalStack(Stack *point, StackNode *node)
{
    if (node->PStackNext == point->base)
    {
        point->top = node;
        return node;
    }
    StackNode *tail = reversalStack(point, node->PStackNext);
    tail->PStackNext = node;
    node->PStackNext = point->base;
    return node;
}

/**
 * @brief 栈反转
 * 修改当前传入的栈
 * @param point 
 * @return Stack* 
 */
Stack *StackReversalO(Stack *point)
{
    if (point == NULL)
        return NULL;
    reversalStack(point, point->top);
    return point;
}