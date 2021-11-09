#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "lexicalAnalyzer/lexical.h"
#include "lexicalAnalyzer/utils.h"
#include <time.h>
#include "lexicalAnalyzer/nfa_Intepretor.h"

void wait(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLK_TCK;
    while (clock() < endwait)
    {
    }
}

int main()
{
    int f = initParse("./reg-test.txt");
    initMatchNfa(nfaSet, "0.1x");
    return 1;
}