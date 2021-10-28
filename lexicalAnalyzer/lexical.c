#include "lexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "utils.h"
#include "setutils.h"

static void initRegParse(char *str);
static void switchOption(char str);
static void otherOptions();
static void stnsOptions();
static void optrOptions();
static void setOptions(char *s);

Stack *OPTR = NULL;      //运算符栈
Stack *STNS = NULL;      //语法树节点栈
NfaNode *rootNfa = NULL; // nfa根节点
NfaPair *nfapaif = NULL;
WholeState *wholeStatus = NULL;

int row = 1;
int col = 0;

int initParse(char *path)
{
    STNS = new_stack();
    OPTR = new_stack();

    nfapaif = (NfaPair *)malloc(sizeof(NfaPair));
    nfapaif->startNode = (NfaNode *)malloc(sizeof(NfaNode));
    nfapaif->endNode = (NfaNode *)malloc(sizeof(NfaNode));
    rootNfa = nfapaif->startNode;
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

    int len = sizeof(str);
    char *s = (char *)malloc(len + 1);
    strcpy(s, &str);
    s[len] = '\0';
    if (1 <= wholeStatus->state <= 3)
    {
        a = b = 0;
        isSet = TRUE;
        setOptions(s);
    }

    if (a)
    {
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
        printf("请勿使用转义字符，暂时不实现");
    }
    free(s);
    s = NULL;
}

void stnsOptions()
{
    wholeStatus->state = PSWsinglechar;
    char *s = spop(STNS);
    printf("STNS:%s\n", s);
    free(s);
    s = NULL;
}

void optrOptions()
{
    wholeStatus->state = PSWoptr;
    char *s = spop(OPTR);
    if (*s == '[')
    {
        setOptions(s);
    }
    printf("OPTR:%s\n", s);
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