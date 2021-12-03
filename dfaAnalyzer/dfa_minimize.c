#include "dfa_minimize.h"
static void seperationAcceptedDfaGroup();
static BOOL spliceGroupOnInput(dfa_group_struct group, Dfa *first, Dfa *next, char c);
static void minimize();
static void sliceDfaGroup();

extern SetRoot dfaGroupManager;
extern SetRoot dfaList;
extern int **dfaStateTransformTable;

static BOOL addNewGroup = FALSE;
static dfa_group_struct newGroup = NULL;
static int **minDfa = NULL;

void MinimizeDFA(SetRoot dfaList, int **dfaStateTransformTable)
{
    resetGroup();
    minimize();
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

        Dfa_Group_Struct *dfagroup = getp_Set_iterator_next(itor);
        My_Iterator *itorDfaGroup = new_Point_Set_iterator(dfagroup->dfagroup);

        Dfa *first = getp_Set_iterator_next(itorDfaGroup);
        Dfa *next = getp_Set_iterator_next(itorDfaGroup);
        // 判断分割 单个节点不在分割
        while (next != NULL)
        {
            for (size_t i = 0; i < ASCII_COUNT; i++)
            {
                if (spliceGroupOnInput(dfagroup, first, next, i) == TRUE)
                {
                    addNewGroup = TRUE;
                    break;
                }
            }
            next = getp_Set_iterator_next(itorDfaGroup);
        }

        my_iterator_free(itorDfaGroup);
        // dfaGroupManager循环内部添加 会影响迭代器
        if (newGroup != NULL)
        {
            addp_set(temp, newGroup);
            newGroup = NULL;
        }
        commitRemove(dfagroup);
    }
    concatDfaGroup(dfaGroupManager, temp);
    set_destory(temp, NULL);
    my_iterator_free(itor);
}

BOOL spliceGroupOnInput(dfa_group_struct group, Dfa *first, Dfa *next, char c)
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

    dfa_group_struct acc = newDfaGroup(TRUE);
    dfa_group_struct noacc = newDfaGroup(TRUE);
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