#include "bool.h"
#include "my_ArrayList.h"
#include "my_map.h"
#include "LR1production.h"
#include "LR1productionManager.h"

typedef struct LR1GrammarState
{
    int stateNum;
    BOOL transitionDone; // 是否已经进行过处理
    My_ArrayList *productionList;
    My_ArrayList *closureSet;
    MapRoot partitions;
    MapRoot transitions;
} LR1GrammarState;

static void LR1makeClosure(LR1GrammarState *state);
static void LR1removeRedundantProduction(LR1GrammarState *state, LR1Production *p);
static void LR1partition(LR1GrammarState *state);

static void LR1MakeTransition(LR1GrammarState *state);
static LR1GrammarState *LR1MakeNextGrammarState(My_ArrayList *productionList);
static void LR1extendFollowTransition(MapRoot transition);

static void LR1GrammarStatePrint(LR1GrammarState *grammarState);
static My_ArrayList *stateList = NULL;
// 语法节点计数器(做id用)
static int stateNumCount = 0;

LR1GrammarState *LR1newGrammarState(My_ArrayList *productionList)
{
    LR1GrammarState *state = my_malloc(sizeof(LR1GrammarState));
    state->productionList = productionList;
    state->stateNum = stateNumCount;
    state->transitionDone = FALSE;

    state->closureSet = ArrayListCreate();
    state->closureSet->equals = (ArrayListDefEquals)LR1productionEquals;
    // 默认闭包
    ArrayListAddAll(state->closureSet, state->productionList);

    state->partitions = newMap(Map_Number);
    state->transitions = newMap(Map_Number);
    return state;
}

LR1GrammarState *LR1getGrammarState(My_ArrayList *productionList)
{
    int index = -1;
    for (size_t i = 0; i < stateList->size; i++)
    {
        LR1GrammarState *cur = ArrayListGetFormPos(stateList, i);
        if (ArrayListEquals(productionList, cur->productionList) == TRUE)
            index = i;
    }
    if (index < 0)
    {
        // 没找到  新建语法节点
        LR1GrammarState *state = LR1newGrammarState(productionList);
        stateNumCount++;
        ArrayListPush(stateList, state);
        return state;
    }
    return ArrayListGetFormPos(stateList, index);
}

void LR1createTransition(LR1GrammarState *state)
{
    if (state->transitionDone == TRUE)
        return;
    state->transitionDone = TRUE;
    printf("\n====make transition=====\n");
    LR1GrammarStatePrint(state);
    // 进行闭包处理 找到所有节点
    LR1makeClosure(state);
    // 进行分割语法节点
    LR1partition(state);
    // 对分割好的节点集合 生成新的语法节点 记录转移路径 并进行下一次的处理
    LR1MakeTransition(state);
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
        // printf("LR1makeClosure %s \n", getSymbolStr(symbol));
        // 终结符跳出本次循环
        if (LR1isSymbolTerminals(symbol) == TRUE)
            continue;
        // 通过符号以及初始化产生式生成的productionMap 获取当前符号为非终结符的 productionList
        // 终结符 获取结果为 NULL
        My_ArrayList *closures = LR1getProduction(symbol);
        My_ArrayList *LookAhead = LR1ProductionFirstMergetC(production);

        for (size_t i = 0; closures != NULL && i < closures->size; i++)
        {
            LR1Production *p = ArrayListGetFormPos(closures, i);
            LR1Production *newP = LR1productionCloneSelf(p);
            LR1AddProductionLookAhead(newP, LookAhead);

            if (ArrayListFindNode(state->closureSet, newP) < 0)
            {
                ArrayListPush(state->closureSet, newP);
                sPointPush(prductionStack, newP);
                LR1removeRedundantProduction(state, newP);
            }
        }
        ArrayListDestroy(LookAhead);
    }
}

void LR1removeRedundantProduction(LR1GrammarState *state, LR1Production *p)
{
    int length = state->closureSet->size - 1;
    while (length >= 0)
    {
        if (LR1productionCoverUp(p, ArrayListGetFormPos(state->closureSet, length)) == TRUE)
            ArrayListDelete(state->closureSet, length);
        length--;
    }
}
// 分割闭包 生成新的语法节点
void LR1partition(LR1GrammarState *state)
{
    for (size_t i = 0; i < state->closureSet->size; i++)
    {
        LR1Production *production = ArrayListGetFormPos(state->closureSet, i);
        SymbolDefine symbol = LR1productionGetDotSymbol(production);

        if (symbol == UNKNOWN_SYMBOL)
            continue;

        My_ArrayList *productionList = MapGetNumNode(state->partitions, symbol);
        if (productionList == NULL)
        {
            productionList = ArrayListCreate();
            productionList->equals = (ArrayListDefEquals)LR1productionEquals;
            MapPutNumNode(state->partitions, symbol, productionList);
        }
        if (ArrayListFindNode(productionList, production) < 0)
            ArrayListPush(productionList, production);
    }
}
// GOTO
// 对分割好的节点集合 生成新的语法节点 记录转移路径 并进行下一次的处理
void LR1MakeTransition(LR1GrammarState *state)
{
    My_Iterator *itor = newMapIterator(state->partitions);
    printf("LR1MakeTransition begin \n");
    while (has_itor_next(itor))
    {
        RbNodeP node = get_itor_next(itor);
        SymbolDefine symbol = node->key.n;
        LR1GrammarState *nextState = LR1MakeNextGrammarState(node->value);
        printf("from state  %d to state %d on %s \n", state->stateNum, nextState->stateNum, getSymbolStr(symbol));
        MapPutNumNode(state->transitions, symbol, nextState);
    }
    my_iterator_free(itor);

    printf("\n LR1MakeTransition end \n");
    // 进行后继处理
    LR1extendFollowTransition(state->transitions);
}

LR1GrammarState *LR1MakeNextGrammarState(My_ArrayList *productionList)
{
    My_ArrayList *newProductionList = ArrayListCreate();
    newProductionList->equals = (ArrayListDefEquals)LR1productionEquals;

    for (size_t i = 0; i < productionList->size; i++)
    {
        LR1Production *p = ArrayListGetFormPos(productionList, i);
        ArrayListPush(newProductionList, LR1productionNextDotForward(p));
    }
    return LR1getGrammarState(newProductionList);
}

void LR1extendFollowTransition(MapRoot transition)
{
    My_Iterator *itor = newMapIterator(transition);
    while (has_itor_next(itor))
    {
        RbNodeP node = get_itor_next(itor);
        LR1createTransition((LR1GrammarState *)node->value);
    }
    my_iterator_free(itor);
}

void LR1GrammarStatePrint(LR1GrammarState *grammarState)
{
    printf("State Number: %d ", grammarState->stateNum);
    for (size_t i = 0; i < grammarState->productionList->size; i++)
    {
        LR1productionPrint(ArrayListGetFormPos(grammarState->productionList, i));
    }
    printf("\n");
}
