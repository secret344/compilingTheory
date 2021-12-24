#include <stdio.h>
#include <string.h>
#include <time.h>
#include "nfa_parse.h"
#include "nfa_Intepretor.h"
#include "dfa_Intepretor.h"
#include "dfa_parse.h"
#include "read_file.h"
#include "utils.h"
#include "my_map.h"
#include "read_str.h"
#include "push_down_DFA.h"

char *regParse(char *str)
{
    char *JsonStr = initParse(str, initReadChar);
    return JsonStr;
}

char *matchStr(char *str)
{
    // initMatchNfa(str);
    char *json = initMatchDfa(str);
    return json;
}

char *getDfaJson()
{
    return dfaJsonStr;
}

int main()
{
    printf("加载webassembly模块  \n");

    initPushDownDfa();
    return 0;
}
