#include "dfa_minimize.h"
static void seperationAcceptedDfaGroup();
static BOOL spliceGroupOnInput(dfa_group_struct group, Dfa *first, Dfa *next, int c);
static void minimize();
static void sliceDfaGroup();
static void creatMiniDfaTransTable();
static void initMiniDfaTransTable();
static cJSON *dfaGroupToArrayJson();
static void viewGroup();

static BOOL addNewGroup = FALSE;
static dfa_group_struct newGroup = NULL;
int **minDfa = NULL;
void destoryMinimizeDfa()
{
    if (minDfa != NULL)
    {
        destoryDfaStateTransformTable(minDfa);
        minDfa = NULL;
    }
    resetGroup();
}

cJSON *MinimizeDFA()
{
    minimize();
    // printf("生成结束,开始打印最小化的dfa节点状态表 : \n");
    // printDfaStateTransformTable(minDfa, dfaGroupManager->size);
    // printf("节点状态表打印完毕. \n");
    // viewGroup();
    cJSON *result = cJSON_CreateObject();
    cJSON *dfaGroup = dfaGroupToArrayJson();
    cJSON *minDfaJson = stateTransformTableToJson(minDfa, ASCII_COUNT, dfaGroupManager->size);
    cJSON_AddItemToObject(result, "dfaGroup", dfaGroup);
    cJSON_AddItemToObject(result, "minDfa", minDfaJson);
    return result;
}

void minimize()
{
    // 初始化分区 将dfa节点分为accepted接收 非接收状态两个分区
    seperationAcceptedDfaGroup();
    do
    {
        addNewGroup = FALSE;
        // 开始进行切割 若产生分割（产生分割有可能导致旧的不可分割产生分割） 重复此步骤
        sliceDfaGroup();
    } while (addNewGroup);
    // 分割完毕 开始创建最小化dfa状态转移表
    creatMiniDfaTransTable();
}

void sliceDfaGroup()
{
    // 对dfaGroup集合分区(i)进行再次分割
    // 计算此时分区(i)字符集c的下一个dfa状态(ic)
    // 保留相同(ic)子集，分割不同子集
    My_Iterator *itor = new_Point_Set_iterator(dfaGroupManager);
    SetRoot temp = new_Set(Set_Struct);
    while (has_Set_iterator_next(itor))
    {
        newGroup = NULL;
        Dfa_Group_Struct *dfagroup = getp_Set_iterator_next(itor);
        My_Iterator *itorDfaGroup = new_Point_Set_iterator(dfagroup->dfagroup);

        Dfa *first = getp_Set_iterator_next(itorDfaGroup);
        Dfa *next = getp_Set_iterator_next(itorDfaGroup);
        // 判断分割 单个节点不在分割
        {
            while (next != NULL)
            {
                for (int i = 0; i < ASCII_COUNT; i++)
                {
                    if (spliceGroupOnInput(dfagroup, first, next, i) == TRUE)
                    {
                        addNewGroup = TRUE;
                        break;
                    }
                }
                next = getp_Set_iterator_next(itorDfaGroup);
            }
        }

        my_iterator_free(itorDfaGroup);
        // dfaGroupManager循环内部添加 会影响迭代器
        if (newGroup != NULL)
        {
            addp_set(temp, newGroup);
        }
        commitRemove(dfagroup);
    }
    concatDfaGroup(dfaGroupManager, temp);
    set_destory(temp, NULL);
    my_iterator_free(itor);
}

BOOL spliceGroupOnInput(dfa_group_struct group, Dfa *first, Dfa *next, int c)
{
    // 跳转后的节点 判断是否在同一分区
    int to_first = dfaStateTransformTable[c][first->stateNum];
    int to_next = dfaStateTransformTable[c][next->stateNum];

    if (getContainingGroup(to_first) != getContainingGroup(to_next))
    {
        // 不在同一分区 进行切割
        if (newGroup == NULL)
        {
            newGroup = newDfaGroup(FALSE);
        }
        addp_set(group->tobeRemove, next);
        addp_set(newGroup->dfagroup, next);
        return TRUE;
    }
    return FALSE;
}

void seperationAcceptedDfaGroup()
{
    My_Iterator *itor = new_Point_Set_iterator(dfaList);
    dfa_group_struct noacc = newDfaGroup(TRUE);
    dfa_group_struct acc = newDfaGroup(TRUE);
    while (has_Set_iterator_next(itor))
    {
        Dfa *dfa = getp_Set_iterator_next(itor);
        if (dfa->accepted == TRUE)
        {
            addp_set(acc->dfagroup, dfa);
        }
        else
        {
            addp_set(noacc->dfagroup, dfa);
        }
    }
    my_iterator_free(itor);
}
/**
 * @brief 创建miniDfa状态转移表
 * 
 */
void creatMiniDfaTransTable()
{
    initMiniDfaTransTable();
    My_Iterator *itor = new_Point_Set_iterator(dfaList);
    // 拿到所有dfa节点
    while (has_Set_iterator_next(itor))
    {
        Dfa *dfa = getp_Set_iterator_next(itor);
        for (int i = 0; i < ASCII_COUNT; i++)
        {
            // 获取dfa状态转移目标节点
            if (dfaStateTransformTable[i][dfa->stateNum] != STATE_FAILURE)
            {
                int toNum = dfaStateTransformTable[i][dfa->stateNum];
                // 找到状态转移集合
                dfa_group_struct fromgroup = getContainingGroup(dfa->stateNum);
                dfa_group_struct togroup = getContainingGroup(toNum);
                // 生成最小化的dfa状态转移表
                minDfa[i][fromgroup->group_num] = togroup->group_num;
            }
        }
    }
    my_iterator_free(itor);
}
// 初始化状态转移表
void initMiniDfaTransTable()
{
    minDfa = (int **)my_malloc((ASCII_COUNT) * sizeof(int *));
    for (int i = 0; i < ASCII_COUNT; i++)
    {
        minDfa[i] = (int *)my_malloc((dfaGroupManager->size) * sizeof(int));
        for (int j = 0; j < dfaGroupManager->size; j++)
        {
            minDfa[i][j] = STATE_FAILURE;
        }
    }
}

void viewGroup()
{
    printf("viewGroup %d \n", dfaList->size);
    My_Iterator *itor = new_Point_Set_iterator(dfaGroupManager);
    while (has_Set_iterator_next(itor))
    {
        Dfa_Group_Struct *dfagroup = getp_Set_iterator_next(itor);
        printf("dfagroup序号 %d \n", dfagroup->group_num);
        My_Iterator *itor1 = new_Point_Set_iterator(dfagroup->dfagroup);
        while (has_Set_iterator_next(itor1))
        {
            Dfa *dfa = getp_Set_iterator_next(itor1);
            printf("打印dfa %d %d \n", dfa->stateNum, dfa->accepted);
        }
        printf("dfagroup单个结束 \n");
        my_iterator_free(itor1);
    }
    my_iterator_free(itor);
    printf("viewGroup end %d \n", dfaList->size);
}

cJSON *dfaGroupToArrayJson()
{
    cJSON *result = cJSON_CreateArray();

    My_Iterator *itor = new_Point_Set_iterator(dfaGroupManager);
    while (has_Set_iterator_next(itor))
    {
        Dfa_Group_Struct *dfagroup = getp_Set_iterator_next(itor);
        cJSON *json = DfaGroupToCJson(dfagroup);
        cJSON_AddItemToArray(result, json);
    }
    my_iterator_free(itor);

    return result;
}