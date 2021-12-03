#include <stdio.h>
#include <string.h>
#include <time.h>
#include "nfa_parse.h"
#include "nfa_Intepretor.h"
#include "dfa_parse.h"
#include "read_file.h"
#include "utils.h"
#include "my_map.h"
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

int dfaParse()
{
    Stack *new = new_stack();
    //   printf("dfaParsesad %d\n", stacksize(nfaSet));
    printf("dfaParse \n");
    while (stacksize(nfaSet))
    {
        NfaPair *node = spop(nfaSet);
        sPointPush(new, node);
        initDfaParse(node);
    }
    sdestory(nfaSet, NULL);
    nfaSet = new;
    printf("dfaParse end \n");
    return 0;
}

int main()
{
    printf("加载webassembly模块 \n");
    return 0;
}
