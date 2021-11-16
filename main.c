#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "nfa_parse.h"
#include "nfa_Intepretor.h"
#include "read_file.h"
#include "utils.h"

// void wait(int seconds)
// {
//     clock_t endwait;
//     endwait = clock() + seconds * CLOCKS_PER_SEC;
//     while (clock() < endwait)
//     {
//     }
// }
char *regParse(char *str)
{
    char *JsonStr = initParse(str, initReadChar);
    return JsonStr;
}

int matchStr(char *str)
{
    initMatchNfa(str);
    return 0;
}

int main()
{
    printf("加载webassembly模块");
    return 0;
}
