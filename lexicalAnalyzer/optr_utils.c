#include "lexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "nfa_Interface.h"

static NfaPair *optrpaif = NULL;
static Stack *optrStack = NULL;
void optrInitStack()
{
    if (!optrStack)
    {
        optrStack = new_stack();
    }
}

void StarClosure(char s)
{
    if (s != '*')
    {
        return;
    }

    optrpaif->startNode->next = curNfa->startNode;

    optrpaif->startNode->next2 = optrpaif->endNode;

    curNfa->endNode->next = optrpaif->endNode;

    curNfa->endNode->next2 = optrpaif->startNode;

    // 链接完成更新当前NODE
    curNfa->startNode = optrpaif->startNode;
    curNfa->endNode = optrpaif->endNode;
}

void PlusClosure(char s)
{
    if (s != '+')
    {
        return;
    }

    optrpaif->startNode->next = curNfa->startNode;

    curNfa->endNode->next = optrpaif->endNode;

    curNfa->endNode->next2 = optrpaif->startNode;

    // 链接完成更新当前NODE
    curNfa->startNode = optrpaif->startNode;
    curNfa->endNode = optrpaif->endNode;
}

void OptionsClosure(char s)
{
    if (s != '?')
    {
        return;
    }

    optrpaif->startNode->next = curNfa->startNode;

    curNfa->endNode->next = optrpaif->endNode;

    optrpaif->startNode->next2 = optrpaif->endNode;

    // 链接完成更新当前NODE
    curNfa->startNode = optrpaif->startNode;
    curNfa->endNode = optrpaif->endNode;
}

void orDispose(char *s)
{
    optrpaif = curNfa; // 保存当前nfa节点，等待下次节点执行或运算
    curNfa = NULL;
    spush(OPTR, s);
    // // 保存上一次节点，等待下次生成节点进行合并
    sOptrPush(optrStack, optrpaif);
}

void bracketDispose(char *s)
{
    if (*s == '(')
    { 
        // 如果是括号构造新的节点链 保存之前的节点链，等待括号运算结束合并
        if (nfapaif)
        {
            sOptrPush(optrStack, nfapaif);
        }
        spush(OPTR, s);
        return;
    }
    // )
    // 括号结束 取出栈内左括号。curNfa赋值为括号生成的节点
    // 等待后续合并到主节点树中
    int n = stacksize(OPTR);
    char *str = spop(OPTR);
    if (n <= 0 || *str != '(')
    {
        printf(") 必须含有相对应的 (,位置 行：%d 列：%d \n", row, col);
    }
    curNfa = nfapaif;
    nfapaif = sOptrPop(optrStack);
    free(str);
    str = NULL;
}

void switchOptr(char *s)
{

    switch (*s)
    {
    case '*':
    case '+':
    case '?':
        wholeStatus->state = PSWoptr;
        optrpaif = (NfaPair *)malloc(sizeof(NfaPair));
        setInitPair(optrpaif);
        StarClosure(*s);
        PlusClosure(*s);
        OptionsClosure(*s);
        wholeStatus->state = PSWdef;
        break;
    case '|':
        optrInitStack();
        orDispose(s);
        break;
    case '(':
    case ')':
        optrInitStack();
        bracketDispose(s);
        break;
    default:
        break;
    }
}

void OptrDispose(char s)
{ // 闭包运算优先级最高
    if (s == '*' || s == '?' || s == '+')
    {
        return;
    }
    // s 当前节点之后的字符串
    char *str = spop(OPTR); // 取出当前运算符栈运算符
    switch (*str)
    {
    case '|':
        printf("");
        // 取出当前运算符栈需要的节点 单步处理的节点不需保存到栈
        NfaPair *n = sOptrPop(optrStack); // 或运算符 next
        NfaPair *b = curNfa;              // 或运算符 next2
        // 进行或链接 合并成curNfa 暂不链接，等待下一个字符处理程序处理
        optrpaif = (NfaPair *)malloc(sizeof(NfaPair)); // 生成两端节点
        setInitPair(optrpaif);
        //  a | b

        //   1 - 2
        // 0       5
        //   3 - 4
        optrpaif->startNode->next = n->startNode;
        optrpaif->startNode->next2 = b->startNode;

        n->endNode->next = optrpaif->endNode;
        b->endNode->next = optrpaif->endNode;

        curNfa = optrpaif;
        break;
    case '(': //括号运算符需要等待字符 ) 取出
    default:
        // 未处理的运算符 放回去交给相应处理函数处理
        spush(OPTR, str);
        break;
    }
    free(str);
    str = NULL;
}