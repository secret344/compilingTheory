#include "data_struct_utils.h"

// 字符串比较 从左到右比较 左边字母越大自身越大
BOOL string_compare_gt(char *a, char *b)
{
    if (*a == '\0' && *b == '\0')
    {
        return COMPARE_EQ;
    }

    while (*a != '\0' || *b != '\0')
    {
        char l = *a++;
        char r = *b++;

        if (r == '\0' && l != '\0')
        {
            return TRUE;
        }

        if (l == '\0' && r != '\0')
        {
            return FALSE;
        }

        if (l != r)
        {
            return l > r;
        }
    }

    return COMPARE_EQ;
}

void StackDestoryEmpty(void *x) {}