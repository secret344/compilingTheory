
#include "dfa_Intepretor.h"
static BOOL viewGroupAccepted(Dfa_Group_Struct *dfaGroup);
// 记录匹配结果
cJSON *result = NULL;

void initMatchDfa(char *s)
{
}

void matchChar()
{
    int cur = 0;
    char c = NULL;
}

void AddResultJson(BOOL isValid)
{
    if (result == NULL)
    {
        result = cJSON_CreateObject();
        cJSON *valid = cJSON_CreateArray();
        cJSON *invalid = cJSON_CreateArray();
        cJSON_AddItemToObject(result, "valid", valid);
        cJSON_AddItemToObject(result, "invalid", invalid);
    }
}

// 查看当前是不是终结节点集
BOOL viewGroupAccepted(Dfa_Group_Struct *dfaGroup)
{
    SetRoot dfagroup = dfaGroup->dfagroup;
    My_Iterator *itor = new_Point_Set_iterator(dfagroup);
    Dfa *dfa = getp_Set_iterator_next(dfagroup);
    my_iterator_free(itor);
    return dfa->accepted;
}