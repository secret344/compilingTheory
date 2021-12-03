#include "dfa_group.h"
static BOOL groupContainsDfa(SetRoot group, int dfaStateNum);
static void destorydfaGroup();
static int GROUP_COUNT = 0;
SetRoot dfaGroupManager = NULL;
void resetGroup()
{
    GROUP_COUNT = 0;
    if (dfaGroupManager != NULL)
    {
        destorydfaGroup();
    }
    dfaGroupManager = NULL;
}

void destorydfaGroup()
{
    My_Iterator *itor = new_Point_Set_iterator(dfaGroupManager);
    while (has_Set_iterator_next(itor))
    {
        Dfa_Group_Struct *dfagroup = getp_Set_iterator_next(itor);
        set_destory(dfagroup->dfagroup, NULL);
        set_destory(dfagroup->tobeRemove, NULL);
        my_free(dfagroup);
    }
    my_iterator_free(itor);
    set_destory(dfaGroupManager, NULL);
}

Dfa_Group_Struct *newDfaGroup(BOOL isAdd)
{
    if (dfaGroupManager == NULL)
    {
        dfaGroupManager = new_Set(Set_Struct);
    }

    dfa_group_struct dfagroup = (dfa_group_struct)my_malloc(sizeof(Dfa_Group_Struct));
    dfagroup->dfagroup = new_Set(Set_Struct);
    dfagroup->tobeRemove = new_Set(Set_Struct);
    dfagroup->group_num = GROUP_COUNT++;
    if (isAdd)
    {
        addp_set(dfaGroupManager, dfagroup);
    }
    return dfagroup;
}
/**
 * @brief 获取dfa节点分区
 * 
 * @param dfaStateNum 
 * @return Dfa_Group_Struct* 
 */
Dfa_Group_Struct *getContainingGroup(int dfaStateNum)
{
    dfa_group_struct result = NULL;
    My_Iterator *itor = new_Point_Set_iterator(dfaGroupManager);
    while (has_Set_iterator_next(itor))
    {
        Dfa_Group_Struct *dfagroup = getp_Set_iterator_next(itor);
        if (groupContainsDfa(dfagroup->dfagroup, dfaStateNum))
        {
            // 存在该节点 返回分区
            result = dfagroup;
            break;
        }
    }
    my_iterator_free(itor);
    return result;
}
/**
 * @brief 判断该分区是否存在dfa节点
 * 
 * @param group 
 * @param dfaStateNum 
 * @return BOOL 
 */
BOOL groupContainsDfa(SetRoot group, int dfaStateNum)
{
    BOOL result = FALSE;
    My_Iterator *itor = new_Point_Set_iterator(group);
    while (has_Set_iterator_next(itor))
    {
        Dfa *dfa = getp_Set_iterator_next(itor);
        if (dfa->stateNum == dfaStateNum)
        {
            result = TRUE;
            break;
        }
    }
    my_iterator_free(itor);
    return result;
}

/**
 * @brief 提交清理
 * @param dfagroup 
 */
void commitRemove(dfa_group_struct dfagroup)
{
    My_Iterator *itor = new_Point_Set_iterator(dfagroup->tobeRemove);
    while (has_Set_iterator_next(itor))
    {
        Dfa *dfa = getp_Set_iterator_next(itor);
        // 清理分区
        removep_set(dfagroup->dfagroup, dfa);
    }
    my_iterator_free(itor);
    // 清理待清理
    set_destory(dfagroup->tobeRemove, NULL);
    dfagroup->tobeRemove = NULL;
    // 清理结束
    dfagroup->tobeRemove = new_Set(Set_Struct);
}

void concatDfaGroup(SetRoot target, SetRoot source)
{
    if (source->size <= 0)
    {
        return;
    }

    My_Iterator *itor = new_Point_Set_iterator(source);
    while (has_Set_iterator_next(itor))
    {
        dfa_group_struct dfaGroup = getp_Set_iterator_next(itor);
        addp_set(target, dfaGroup);
    }
    my_iterator_free(itor);
}