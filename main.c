#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "lexical.h"
#include "nfa_Intepretor.h"
#include "read_file.h"
#include <emscripten.h>

// void wait(int seconds)
// {
//     clock_t endwait;
//     endwait = clock() + seconds * CLOCKS_PER_SEC;
//     while (clock() < endwait)
//     {
//     }
// }
int regParse(char *str)
{
    int f = initParse(str, initReadChar);
    return f;
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
