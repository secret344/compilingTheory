
#ifndef _DFA_INTERFACE_
#define _DFA_INTERFACE_
#include "lex_stack.h"
#include "nfa_Interface.h"
#include "my_set.h"

#define STATE_FAILURE -1

typedef struct Dfa
{
    int stateNum;      // dfa编号
    SetRoot nfaStates; // dfa内nfa状态集
    BOOL accepted;     // 接受状态
} Dfa;

#endif