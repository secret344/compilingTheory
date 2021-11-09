#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_file.h"

static void initParse(char *str, fun_t cb);
int row = 1; //行
int col = 0; //列

int initReadFile(char *path, fun_t cb)
{
    FILE *fp = NULL;
    char buff[255];
    fp = fopen(path, "r");

    if (!fp)
        return EXIT_FAILURE;

    while (fgets(buff, 255, (FILE *)fp))
    {
        initParse(buff, cb);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

void initParse(char *str, fun_t cb)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        col++;
        if (str[i] == '\n')
        {
            row++;
            col = 0;
        }
        int d = str[i];
        if (d < 0 || d > 128)
        {
            printf("行:%d,列:%d 字符%d不符合规则.请使用ascii码表内英文字符.\n", row, col, str[i]);
        }
        cb(str[i]);
    }
}