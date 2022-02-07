#include "LR1GrammarStateManager.h"
#include "LR1GrammarState.c"

void LR1BuildTransitionStateMachine()
{
    // 初始化缓存语法节点的数组
    stateList = ArrayListCreate();
    // 创建首个语法节点 STMT
    // 对该节点进行处理
    // 当存在已经创建过的语法节点时 也就是stateList已经缓存过的节点 返回已经存在的
    LR1GrammarState *state = LR1getGrammarState(LR1getProduction(STMT));
    LR1createTransition(state);
}