#include "lexical.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"

void initRegParse(char *str);
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
        printf("initRegParse: %c行: %d 列: %d\n", str[i], row, col);
    }
}

void printOutput()
{
}