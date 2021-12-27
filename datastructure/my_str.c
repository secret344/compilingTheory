#include "my_str.h"

char *concatstr(char *target, char *source)
{
    int len = strlen(target);
    int len1 = strlen(source);
    char *s = (char *)my_malloc(len + len1 + 1);
    strcpy(s, target);
    strcat(s, source);
    return s;
}

char *concatStrAndChar(char *target, char source)
{
    int len = strlen(target);
    char *temp = my_malloc(2);
    temp[0] = source;
    temp[1] = '\0';
    char *s = concatstr(target, temp);
    my_free(temp);
    return s;
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

char *getSetLetter(char a, char b)
{
    int len = b - a + 1;
    if (len < 0)
    {
        return NULL;
    }
    char *s = (char *)my_malloc(len + 1);
    for (size_t i = 0; i < len; i++)
    {
        s[i] = a++;
    }
    s[len] = '\0';
    return s;
}
/**
 * 去除字符串重复字符
*/
char *noStrRepetition(char *str)
{
    int len = strlen(str);
    char *repe = (char *)my_malloc(len + 1);
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        char s = str[i];
        repe[count] = '\0';
        BOOL is = findChar(s, repe);
        if (!is)
        {
            repe[count++] = s;
        }
    }
    repe[count] = '\0';
    // 节省内存
    char *result = (char *)my_malloc(strlen(repe) + 1);
    strcpy(result, repe);
    my_free(repe);
    repe = NULL;
    return result;
}
/**
 * 取补集
*/
char *setComplement(char *str)
{
    char s[129];
    int count = 0;
    // TODO 去掉ASCII码表首个字符 json格式化显示异常（未修复）
    for (int i = 0; i < ASCII_COUNT; i++)
    {
        int is = findChar(i, str);
        if (!is)
        {
            s[count++] = i;
        }
    }
    s[count] = '\0';
    char *result = (char *)my_malloc(strlen(s) + 1);
    strcpy(result, s);
    return result;
}