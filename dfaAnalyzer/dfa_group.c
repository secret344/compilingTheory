#include "dfa_group.h"
static int GROUP_COUNT = 0;

void resetGroupCount()
{
    GROUP_COUNT = 0;
}

Dfa_Group_Struct *newDfaGroup()
{
    dfa_group_struct dfagroup = (dfa_group_struct)my_malloc(sizeof(Dfa_Group_Struct));
    dfagroup->dfagroup = new_Set(RB_Struct);
    dfagroup->tobeRemove = new_Set(RB_Struct);
    dfagroup->group_num = GROUP_COUNT++;
    return dfagroup;
}

/**
 * @brief 提交清理
 * TODO
 * @param dfagroup 
 */
void commitRemove(dfa_group_struct dfagroup)
{
    set_destory(dfagroup, NULL);
}
