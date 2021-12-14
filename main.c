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

char *dfaParse()
{
    cJSON *root = cJSON_CreateObject();
    Stack *new = new_stack();
    // printf("dfaParse \n");
    while (stacksize(nfaSet))
    {
        NfaPair *node = spop(nfaSet);
        char *name = node->endNode->name;
        sPointPush(new, node);

        cJSON *dfajson = initDfaParse(node);
        cJSON_AddItemToObject(root, name, dfajson);
    }
    sdestory(nfaSet, NULL);
    nfaSet = new;
    // printf("dfaParse end \n");
    printfM();
    char *s = cJSON_Print(root);
    cJSON_Delete(root);
    return s;
}

int main()
{
    printf("加载webassembly模块 \n");
    return 0;
}
