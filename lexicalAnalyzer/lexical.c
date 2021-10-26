#include "lexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "stack.h"

void initRegParse(char *str);
void switchOption(char str);

int row = 1;
int col = 0;

int initParse(char *path)
{
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
            printf("行:%d,列:%d 字符%d不符合规则.请使用英文字符.\n", row, col, str[i]);
        }
        switchOption(str[i]);
    }
}

void switchOption(char str)
{
    // [ ]  ( ) : *
    // 1 - 9  a - z  A - Z . _
    // + = |

    // printf("initRegParse: %c行: %d 列: %d\n", str, row, col);
}