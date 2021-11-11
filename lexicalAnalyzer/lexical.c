#include "lexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "set_utils.h"
#include "stns_utils.h"
#include "optr_utils.h"
#include "../readfile/read_file.h"
#include "nfa_Interface.h"

static void initRegParse(char *str);
static void switchOption(char str);
static void otherOptions();
static void stnsOptions();
static void optrOptions();
static void setOptions(char *s);
static void checkUnion(char s);
static void judgeBlock(char str);

Stack *OPTR = NULL;             //运算符栈
Stack *STNS = NULL;             //语法树节点栈
NfaPair *curNfa = NULL;         // 当前正在处理的节点
NfaPair *nfapaif = NULL;        // 当前正在处理的节点树
WholeState *wholeStatus = NULL; // 当前程序状态
Stack *nfaSet = NULL;

int initParse(char *path)
{
    STNS = new_stack();
    OPTR = new_stack();
    nfaSet = new_stack();

    wholeStatus = (WholeState *)malloc(sizeof(WholeState));
    wholeStatus->state = PSWdef;

    int status = initReadFile(path, judgeBlock);
    checkUnion('0');
    return status;
}

void judgeBlock(char str)
{
    static BOOL isJudge = FALSE;
    static char name[255];
    static int count = 0;
    if (str == '\r' || str == '\n' || str == EOF)
    {
        checkUnion('0');
        isJudge = FALSE;
        if (nfapaif == NULL)
        {
            printf("错误的格式，请检查行%d;列%d. 回车换行请忽略此提示.", row, col);
            return;
        }
        nfapaif->endNode->name = malloc(strlen(name) + 1);
        strcpy(nfapaif->endNode->name, name);
        sOptrPush(nfaSet, nfapaif);
        name[count] = '0';
        count = 0;
        nfapaif = NULL;
        return;
    }

    if (!isJudge)
    {
        if (str == ':')
        {
            name[count] = '\0';
            isJudge = TRUE;
        }
        else
        {
            name[count++] = str;
        }
        return;
    }

    switchOption(str);
}

void switchOption(char str)
{
    BOOL isOther = FALSE;

    int a = isSTNS(str);
    int b = isOPTR(str);
    checkUnion(str);
    int len = sizeof(str);
    char *s = (char *)malloc(len + 1);
	s[0] = str;
    s[1] = '\0';
    if (1 <= wholeStatus->state && wholeStatus->state <= 3)
    {
        // 当前状态为 生成集合
        a = b = 0;
        isOther = TRUE;
        setOptions(s);
    }

    if (a || wholeStatus->state == PSWESC)
    {
        // 转意字符之后符号作为字符解析
        b = 0;
        isOther = TRUE;
        spush(STNS, s);
        stnsOptions();
    }

    if (b)
    {
        spush(OPTR, s);
        optrOptions();
    }

    if (!a && !b && !isOther)
    {
        spush(OPTR, s);
        otherOptions();
    }

    free(s);
    s = NULL;
}

void otherOptions()
{
    char *s = spop(OPTR);
    if (*s == '\\')
    {
        // 转义字符
        wholeStatus->state = PSWESC;
    }
    else
    {
        printf("otherOptions行:%d,列:%d 字符%c不符合规则.请使用符合规定的字符.\n", row, col, s);
    }
    free(s);
    s = NULL;
}

void stnsOptions()
{
    char *s = spop(STNS);
    stnsInitfun(*s);
    if (wholeStatus->state == PSWESC)
    {
        stnsDeffun(*s);
        free(s);
        s = NULL;
        return;
    }

    switch (*s)
    {
    case '.':
        stnsDotfun();
        break;
    default:
        stnsDeffun(*s);
        break;
    }
    free(s);
    s = NULL;
}

void optrOptions()
{
    char *s = spop(OPTR);
    switch (*s)
    {
    case '[':
        setOptions(s);
        break;
    case '*':
    case '+':
    case '?':
    case '(':
    case ')':
    case '|':
        switchOptr(s);
        break;
    default:
        break;
    }
    free(s);
    s = NULL;
}

// 字符集合
void setOptions(char *s)
{
    if (wholeStatus->state > 3 || wholeStatus->state < 1)
    {
        setInitfun();
        return;
    }

    switch (*s)
    {
        // 忽略转义字符 空格
    case '\\':
    case ' ':
        break;
    case '^':
        setNOTfun();
        break;
    case '-':
        setStartfun();
        break;
    case ']':
        setEndfun();
        break;
    default:
        setMainfun(s);
        break;
    }
}

void checkUnion(char s)
{
    // 检查运算符栈
    int num = stacksize(OPTR);
    if (num > 0 && curNfa)
    {
        // 运算符栈存在未处理运算符，进行运算符处理方法
        OptrDispose(s);
    }

    switch (s)
    {
    case '|':
    case '*':
    case '+':
    case '?':
        // 如果是闭包 不做链接操作
        // 括号优先级另说
        break;
    default:
        if (curNfa)
        {
            if (!nfapaif)
            {
                nfapaif = curNfa;
            }
            else
            {
                nfapaif->endNode->next = curNfa->startNode;
                nfapaif->endNode = curNfa->endNode;
            }
            curNfa = NULL;
        }
        break;
    }
}