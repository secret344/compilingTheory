#ifndef _DFA_MINIMIZE_
#define _DFA_MINIMIZE_
#include "dfa_group.h"
#include "dfa_parse.h"

typedef struct Dfa_Info_Set
{
    int first;
    char *name;
    int **minidfa;
    SetRoot dfaGroupManager;
    SetRoot dfaList;
} Dfa_Info_Set;
extern SetRoot dfainfo;
cJSON *MinimizeDFA(char *name);
void destoryDfaInfo();
#endif