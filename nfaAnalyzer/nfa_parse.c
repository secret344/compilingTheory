#include "nfa_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "set_utils.h"
#include "stns_utils.h"
#include "optr_utils.h"
#include "read_file.h"
#include "nfa_Interface.h"
#include "cJSON.h"
#include "dfa_parse.h"

static void initRegParse(char *str);
static void switchOption(char str);
static void otherOptions();
static void stnsOptions();
static void optrOptions();
static void setOptions(char *s);
static void checkUnion(char s);
static void judgeBlock(char str);
static void nfaPaifDestory(NfaPair *node);
static char *getJsonNfa();
static void resetNfaSet();

Stack *OPTR = NULL;             //运算符栈
Stack *STNS = NULL;             //语法树节点栈
NfaPair *curNfa = NULL;         // 当前正在处理的节点
NfaPair *nfapaif = NULL;        // 当前正在处理的节点树
WholeState *wholeStatus = NULL; // 当前程序状态
Stack *nfaSet = NULL;
char *NfaJsonStr = NULL;
int StateNum = 0;

char *initParse(char *path, fun_lex parseFun)
{
    if (NfaJsonStr != NULL)
    {
        cJSON_free(dfaJsonStr);
        dfaJsonStr = NULL;
    }

    resetNfaSet();
    wholeStatus->state = PSWdef;
    int status = parseFun(path, judgeBlock);
    NfaJsonStr = getJsonNfa();
    dfaParse();
    return NfaJsonStr;
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
        nfapaif->endNode->name = my_malloc(strlen(name) + 1);
        strcpy(nfapaif->endNode->name, name);
        // 保存正则生成的json字符串
        sPointPush(nfaSet, nfapaif);
        name[count] = '0';
        count = 0;
        nfapaif = NULL;
        StateNum = 0;
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
    char *s = (char *)my_malloc(len + 1);
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

    my_free(s);
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
        printf("otherOptions行:%d,列:%d 字符%s不符合规则.请使用符合规定的字符.\n", row, col, s);
    }
    my_free(s);
    s = NULL;
}

void stnsOptions()
{
    char *s = spop(STNS);
    stnsInitfun(*s);
    if (wholeStatus->state == PSWESC)
    {
        stnsDeffun(*s);
        goto end;
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
end:
    my_free(s);
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
    my_free(s);
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
            if (nfapaif == NULL)
            {
                nfapaif = curNfa;
            }
            else
            {
                nfapaif->endNode->next = curNfa->startNode;
                nfapaif->endNode = curNfa->endNode;
                my_free(curNfa);
            }
            curNfa = NULL;
        }
        break;
    }
}

void nfaNodeDestory(NfaNode *start, Stack *skPoint)
{
    if (start->stateNum == -1)
    {
        return;
    }

    NfaNode *next1 = start->next;
    NfaNode *next2 = start->next2;

    if (start->edge == -2)
    {
        my_free(start->inputset);
        start->inputset = NULL;
    }

    start->stateNum = -1;
    sPointPush(skPoint, start);

    if (next1)
    {
        nfaNodeDestory(next1, skPoint);
    }

    if (next2)
    {
        nfaNodeDestory(next2, skPoint);
    }
}

char *getJsonNfa()
{
    if (stacksize(nfaSet) <= 0)
    {
        return "{\"reject\":\"什么都没得\"}";
    }
    cJSON *root = cJSON_CreateObject();
    Stack *new = new_stack();
    while (stacksize(nfaSet) > 0)
    {
        NfaPair *node = spop(nfaSet);
        JsonNfaParse(node->startNode, root, node->endNode->name);
        sPointPush(new, node);
    }
    sdestory(nfaSet, NULL);
    nfaSet = new;
    char *string = cJSON_Print(root);
    cJSON_Delete(root);
    return string;
}

void resetNfaSet()
{
    StateNum = 0;
    if (STNS == NULL && OPTR == NULL)
    {
        STNS = new_stack();
        OPTR = new_stack();
    }

    if (wholeStatus == NULL)
    {
        wholeStatus = (WholeState *)my_malloc(sizeof(WholeState));
    }

    if (!nfaSet)
    {
        nfaSet = new_stack();
        return;
    }
    Stack *skPoint = new_stack();
    while (stacksize(nfaSet) > 0)
    {
        NfaPair *node = spop(nfaSet);
        my_free(node->endNode->name);
        nfaNodeDestory(node->startNode, skPoint);
        my_free(node);
    }
    sdestory(skPoint, NULL);
}