#include "bool.h"
#include <string.h>
#include "lexical.h"
#include <stdlib.h>
#include "utils.h"

// [ ]  ( ) : *
// 1 - 9  a - z  A - Z . _
// + = |
//语法树节点栈
BOOL isSTNS(char str)
{
    char s[] = "abcdzAZ19_ ";
    return findChar(str, s);
}
//运算符栈
BOOL isOPTR(char str)
{
    char s[] = "+=|-[]()";
    return findChar(str, s);
}

BOOL findChar(char s, char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (s == str[i])
        {
            return TRUE;
        }
    }
    return FALSE;
}
// TODO 暂时不实现
char *ESCmatch(char s)
{
    char *result;
    switch (s)
    {
    case 'd':
        result = "0123456789";
        break;
    case 'D':
        result = "0123456789";
        break;
    case 'n':
        result = "\n";
        break;
    default:
        break;
    }
}

char *getSetLetter(char a, char b)
{
    int len = b - a + 1;
    if (len < 0)
    {
        return NULL;
    }
    char *s = malloc(len + 1);
    for (size_t i = 0; i < len; i++)
    {
        s[i] = a++;
    }
    s[len] = '\0';
    return s;
}

char *concatstr(char *target, char *source)
{
    int len = strlen(target);
    int len1 = strlen(source);
    char *s = malloc(len + len1 + 1);
    strcpy(s, target);
    strcat(s, source);
    return s;
}
