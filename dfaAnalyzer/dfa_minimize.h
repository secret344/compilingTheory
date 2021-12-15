#ifndef _DFA_MINIMIZE_
#define _DFA_MINIMIZE_
#include "dfa_group.h"
#include "dfa_parse.h"

extern int **minDfa;
cJSON *MinimizeDFA();
void destoryMinimizeDfa();

#endif