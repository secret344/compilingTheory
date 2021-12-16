
#include "dfa_Intepretor.h"
static BOOL viewGroupAccepted(Dfa_Group_Struct *dfaGroup);
static void AddResultJson(BOOL isValid, int start, int end, char *type);
static MatchBackType *matchChar(char *s, MatchBackType *mt);

static int count = 0;
static int **curTable = NULL;
static SetRoot curDfaM = NULL;
// 记录匹配结果
cJSON *result = NULL;

void initMatchDfa(char *s)
{
    count = 0;
    int maxLen = strlen(s);

    while (count < maxLen)
    {
        MatchBackType ResultMt[2] = {FALSE, 0};
        // 循环所有正则生成的dfa
        My_Iterator *itor = new_Point_Set_iterator(dfainfo);
        while (has_Set_iterator_next(itor))
        {
            MatchBackType mtt[2];
            Dfa_Info_Set *node = getp_Set_iterator_next(itor);
            // 初始化当前参数
            curTable = node->minidfa;
            curDfaM = node->dfaGroupManager;
            // 进行匹配
            matchChar(s, mtt);
        }
        my_iterator_free(itor);
    }

    // 结果添加入json
    // AddResultJson(isV, start, count, type);
}

MatchBackType *matchChar(char *s, MatchBackType *mt)
{
    int **dfaSTT = curTable;
    int cur = 0;
    int start = count;
    char c = NULL;
    while (cur != -1)
    {
        c = s[start++];
        int next = dfaSTT[c][cur];
        // 如果目标dfa集为-1 则终止循环 此时匹配已经结束
        if (next == -1)
        {
            // 匹配结束 取出最后一次匹配dfa集
            dfa_group_struct dfagroup = getContainingGroupForList(cur, curDfaM);
            // 是否是终结节点集合
            BOOL isV = viewGroupAccepted(dfagroup);
            mt[0].lastAccepted = isV; // 是否匹配成功
            mt[1].num = start;        // 匹配结束节点
            break;
        }
        cur = next;
    }
    return mt;
}

// isValid是否有效匹配 start起始位 end结束位 content匹配项 type 匹配类型
void AddResultJson(BOOL isValid, int start, int end, char *type)
{
    if (result == NULL)
    {
        result = cJSON_CreateObject();
        cJSON_AddItemToObject(result, "valid", cJSON_CreateArray());
        cJSON_AddItemToObject(result, "invalid", cJSON_CreateArray());
    }

    cJSON *target = NULL;
    if (isValid)
    {
        target = cJSON_GetObjectItem(result, "valid");
    }
    else
    {
        target = cJSON_GetObjectItem(result, "invalid");
    }

    // start起始位 end结束位 content匹配项 type 匹配类型
    cJSON *n = cJSON_CreateObject();
    cJSON_AddItemToObject(n, "start", cJSON_CreateNumber(start));
    cJSON_AddItemToObject(n, "end", cJSON_CreateNumber(end));
    cJSON_AddItemToObject(n, "type", cJSON_CreateString(type));

    cJSON_AddItemToArray(target, n);
}

// 查看当前是不是终结节点集
BOOL viewGroupAccepted(Dfa_Group_Struct *dfaGroup)
{
    SetRoot group = dfaGroup->dfagroup;
    My_Iterator *itor = new_Point_Set_iterator(group);
    Dfa *dfa = getp_Set_iterator_next(group);
    my_iterator_free(itor);
    return dfa->accepted;
}