#include "dfa_group.h"
static BOOL groupContainsDfa(SetRoot group, int dfaStateNum);
static int GROUP_COUNT = 0;
SetRoot dfaGroupManager = NULL;
void resetGroupCount()
{
    GROUP_COUNT = 0;
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
    My_Iterator *itor = new_Point_Set_iterator(dfaGroupManager);
    while (has_Set_iterator_next(itor))
    {
        Dfa_Group_Struct *dfagroup = getp_Set_iterator_next(itor);
        if (groupContainsDfa(dfagroup->dfagroup, dfaStateNum))
        {
            my_iterator_free(itor);
            // 存在该节点 返回分区
            return dfagroup;
        }
    }
    my_iterator_free(itor);
    return NULL;
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
    My_Iterator *itor = new_Point_Set_iterator(group);
    while (has_Set_iterator_next(itor))
    {
        Dfa *dfa = getp_Set_iterator_next(itor);
        if (dfa->stateNum == dfaStateNum)
        {
            my_iterator_free(itor);
            return TRUE;
        }
    }
    my_iterator_free(itor);
    return FALSE;
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
}

void concatDfaGroup(SetRoot target, SetRoot source)
{
    My_Iterator *itor = new_Point_Set_iterator(source);
    while (has_Set_iterator_next(itor))
    {
        dfa_group_struct dfaGroup = getp_Set_iterator_next(itor);
        addp_set(target, dfaGroup);
    }
    my_iterator_free(itor);
}