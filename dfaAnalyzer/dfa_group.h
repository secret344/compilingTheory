#ifndef _DFA_GROUP_
#define _DFA_GROUP_
#include "my_set.h"
#include "dfa_interface.h"
#define DfaGroupContains(dfa, target) \
    \hasp_set(dfa->dfagroup, target)

#define DfaGroupSize(dfa) \
    \(dfa->dfagroup->size)

typedef struct Dfa_Group_Struct
{
    int group_num;
    SetRoot dfagroup;
    SetRoot tobeRemove;
} Dfa_Group_Struct, *dfa_group_struct;

Dfa_Group_Struct *newDfaGroup(BOOL isAdd);
Dfa_Group_Struct *getContainingGroup(int dfaStateNum);
void commitRemove(dfa_group_struct dfagroup);
void resetGroupCount();
void concatDfaGroup(SetRoot target, SetRoot source);
#endif