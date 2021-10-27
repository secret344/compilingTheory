#include "bool.h"
#include <string.h>

static BOOL findChar(char s, char str[]);

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
