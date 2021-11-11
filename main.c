#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "lexical.h"
#include "nfa_Intepretor.h"

void wait(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait)
    {
    }
}
int main()
{
    int f = initParse("./reg-test.txt");
    if (!f)
    {
        initMatchNfa(nfaSet, "0.1le t0a 2.2 () == += -- -=,;'123'");
    }
    else
    {
        printf("未找到文件");
    }
    // wait(6000);
    return f;
}
