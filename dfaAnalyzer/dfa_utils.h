#ifndef _DFA_UTILS_
#define _DFA_UTILS_
#include "dfa_interface.h"

// 新建dfa节点
// input: nfa集合(栈模拟)
Dfa *getDfaFromNfaSet(Stack *input);
// 判断dfa集合是否已经存在closure相应的dfa节点
Dfa *isNfaStatesExistInDfa(Stack *closure, SetRoot dfaList);
// 临时的Set转为栈结构
void set_To_Stack(Stack *target, SetRoot source);
void resetStateNum();
void printDfaStateTransformTable(int **a, int count);
#endif
