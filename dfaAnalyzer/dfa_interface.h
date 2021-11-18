
#ifndef _DFA_INTERFACE_
#define _DFA_INTERFACE_
#include "lex_stack.h"
#include "nfa_Interface.h"

#define STATE_FAILURE -1

typedef struct Dfa
{
    int stateNum;     // dfa编号
    Stack *nfaStates; // dfa内nfa状态集(栈代替)
    BOOL accepted;    // 接受状态
} Dfa;

#endif