#include "read_str.h"
static BOOL readflush(Read_Str *file);
static char str_advance(Read_Str *file);

Read_Str *newReadStr(const char *str)
{
    Read_Str *rs = my_malloc(sizeof(Read_Str));
    rs->buff = str;

    rs->next = 0;
    rs->isEnd = FALSE;
    rs->advance = (char (*)(void *))str_advance;

    rs->row = 1;
    rs->col = 0;
    return rs;
}

char str_advance(Read_Str *file)
{
    if (file->isEnd == TRUE)
        return EOF;
    char c = file->buff[file->next];
    // 缓冲区到结尾
    if (c == '\0')
    {
        file->isEnd = TRUE;
        return EOF;
    }

    if (c == '\n')
    {
        file->row++;
        file->col = 0;
    }
    file->next++;
    file->col++;
    return c;
}
