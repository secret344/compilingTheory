#include "lexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "utils.h"

static void initRegParse(char *str);
static void switchOption(char str);
static void otherOptions(char str);
static void stnsOptions();
static void optrOptions();

Stack *OPTR = NULL; //运算符栈
Stack *STNS = NULL; //语法树节点栈

int row = 1;
int col = 0;

int initParse(char *path)
{
    STNS = new_stack();
    OPTR = new_stack();

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
        if (d < 0 || d > 255)
        {
            printf("行:%d,列:%d 字符%d不符合规则.请使用ascii码表内英文字符.\n", row, col, str[i]);
        }
        switchOption(str[i]);
    }
}

void switchOption(char str)
{
    int a = isSTNS(str);
    int b = isOPTR(str);
    int len = sizeof(str);
    char *s = (char *)malloc(len + 1);
    strcpy(s, &str);
    s[len] = '\0';
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
    free(s);
    s = NULL;
    if (!a && !b)
    {
        otherOptions(str);
    }
}

void otherOptions(char str)
{
    printf("otherOptions行:%d,列:%d 字符%c不符合规则.请使用符合规定的字符.\n", row, col, str);
}

void stnsOptions()
{
    char *s = spop(STNS);
    printf("STNS:%s\n", s);
    free(s);
    s = NULL;
}

void optrOptions()
{
    char *s = spop(OPTR);
    printf("OPTR:%s\n", s);
    free(s);
    s = NULL;
}