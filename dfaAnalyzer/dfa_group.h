#ifndef _DFA_GROUP_
#define _DFA_GROUP_
#include "my_set.h"
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

#endif