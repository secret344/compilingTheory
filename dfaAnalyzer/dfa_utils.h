#ifndef _DFA_UTILS_
#define _DFA_UTILS_
#include "dfa_interface.h"

// 新建dfa节点
// input: nfa集合(栈模拟)
Dfa *getDfaFromNfaSet(Stack *input);
#endif