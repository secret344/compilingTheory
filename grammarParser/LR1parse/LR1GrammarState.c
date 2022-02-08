#include "bool.h"
#include "my_ArrayList.h"
#include "my_map.h"
#include "LR1production.h"
#include "LR1productionManager.h"
static void LR1makeClosure(LR1GrammarState *state);

typedef struct LR1GrammarState
{
    int stateNum;
    BOOL transitionDone; // 是否已经进行过处理
    My_ArrayList *productionList;
    My_ArrayList *closureSet;
} LR1GrammarState;

static My_ArrayList *stateList = NULL;
// 语法节点计数器(做id用)
static int stateNumCount = 0;

LR1GrammarState *LR1newGrammarState(My_ArrayList *productionList)
{
    LR1GrammarState *state = my_malloc(sizeof(LR1GrammarState));
    state->productionList = productionList;
    state->stateNum = stateNumCount;
    state->transitionDone = FALSE;
    return state;
}

LR1GrammarState *LR1getGrammarState(My_ArrayList *productionList)
{
    int index = -1;
    for (size_t i = 0; i < stateList->size; i++)
    {
        LR1GrammarState *cur = ArrayListGetFormPos(stateList, i);
        if (ArrayListEquals(productionList, cur->productionList))
            index = i;
    }
    if (index < 0)
    {
        // 没找到  新建语法节点
        LR1GrammarState *state = LR1newGrammarState(productionList);
        stateNumCount++;
        return state;
    }
    return ArrayListGetFormPos(stateList, index);
}

void LR1createTransition(LR1GrammarState *state)
{
    if (state->transitionDone == TRUE)
        return;
    state->transitionDone == TRUE;
    printf("\n====make transition=====\n");
    // 进行闭包处理 找到所有节点
    LR1makeClosure(state);
}

void LR1makeClosure(LR1GrammarState *state)
{
    Stack *prductionStack = new_stack();
    // 创建产生式栈 方便进行闭包操作
    for (size_t i = 0; i < state->productionList->size; i++)
        sPointPush(prductionStack, ArrayListGetFormPos(state->productionList, i));
    while (stacksize(prductionStack) > 0)
    {
        LR1Production *production = spop(prductionStack);
        // 获取当前dot指向的的符号
        SymbolDefine symbol = LR1productionGetDotSymbol(production);
        // 通过符号以及初始化产生式生成的productionMap 获取当前符号为非终结符的 productionList
        // 终结符 获取结果为 NULL
        My_ArrayList *closures = LR1getProduction(symbol);


        for (size_t i = 0; closures != NULL && i < closures->size; i++)
        {
            LR1Production *p = ArrayListGetFormPos(closures, i);
            if (ArrayListFindNode(state->closureSet, p) < 0)
            {
                ArrayListPush(state->closureSet, p);
                sPointPush(prductionStack, p);
            }
        }
    }
}