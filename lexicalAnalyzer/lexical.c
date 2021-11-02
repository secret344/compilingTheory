#include "lexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "utils.h"
#include "set_utils.h"
#include "stns_utils.h"

static void initRegParse(char *str);
static void switchOption(char str);
static void otherOptions();
static void stnsOptions();
static void optrOptions();
static void setOptions(char *s);
static void checkUnion(char s);

Stack *OPTR = NULL;     //运算符栈
Stack *STNS = NULL;     //语法树节点栈
NfaPair *curNfa = NULL; // nfa根节点
NfaPair *nfapaif = NULL;
WholeState *wholeStatus = NULL;

int row = 1;
int col = 0;

int initParse(char *path)
{
    STNS = new_stack();
    OPTR = new_stack();

    wholeStatus = (WholeState *)malloc(sizeof(WholeState));
    wholeStatus->state = PSWdef;

    FILE *fp = NULL;
    char buff[255];
    fp = fopen(path, "r");

    if (!fp)
        return EXIT_FAILURE;

    while (fgets(buff, 255, (FILE *)fp))
    {

        initRegParse(buff);
    }

    fclose(fp);
    checkUnion('0');
    return EXIT_SUCCESS;
}

void initRegParse(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        col++;
        if (str[i] == '\n')
        {
            row++;
            col = 0;
            continue;
        }
        int d = str[i];
        if (d < 0 || d > 128)
        {
            printf("行:%d,列:%d 字符%d不符合规则.请使用ascii码表内英文字符.\n", row, col, str[i]);
        }
        switchOption(str[i]);
    }
}

void switchOption(char str)
{
    BOOL isSet = FALSE;

    int a = isSTNS(str);
    int b = isOPTR(str);
    checkUnion(str);
    int len = sizeof(str);
    char *s = (char *)malloc(len + 1);
    strcpy(s, &str);
    s[len] = '\0';
    if (1 <= wholeStatus->state && wholeStatus->state <= 3)
    {
        // 当前状态为 生成集合
        a = b = 0;
        isSet = TRUE;
        setOptions(s);
    }

    if (a || wholeStatus->state == PSWESC)
    {
        // 转意字符之后符号作为字符解析
        b = 0;
        spush(STNS, s);
        stnsOptions();
    }

    if (b)
    {
        spush(OPTR, s);
        optrOptions();
    }

    if (!a && !b && !isSet)
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
    printf("otherOptions行:%d,列:%d 字符%s不符合规则.请使用符合规定的字符.\n", row, col, s);
    if (*s == '\\')
    {
        // 转义字符
        wholeStatus->state = PSWESC;
    }
    free(s);
    s = NULL;
}

void stnsOptions()
{
    char *s = spop(STNS);
    stnsInitfun(*s);
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
    wholeStatus->state = PSWoptr;
    char *s = spop(OPTR);
    switch (*s)
    {
    case '[':
        setOptions(s);
        break;
    case '*':
    case '+':
    case '?':
        // 创建闭包

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
        // 忽略转义字符
    case '\\':
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
    if (!nfapaif)
    {
        nfapaif = (NfaPair *)malloc(sizeof(NfaPair));
        setInitPair(nfapaif);
    }

    switch (s)
    {
    case '*':
    case '+':
    case '?':
        // 如果是闭包 不做链接操作
        // 括号优先级另说
        break;
    default:
        if (curNfa)
        {
            nfapaif->endNode->next = curNfa->startNode;
            nfapaif->endNode = curNfa->endNode;
            curNfa = NULL;
        }
        break;
    }
}