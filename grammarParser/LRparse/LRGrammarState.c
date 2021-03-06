#include "bool.h"
#include "my_ArrayList.h"
#include "my_map.h"
#include "LRproduction.h"
#include "LRproductionManager.h"

typedef struct LRGrammarState
{
    BOOL printInfo;
    BOOL transitionDone;
    int stateNum;
    My_ArrayList *productions;
    My_ArrayList *closureSet;
    MapRoot transition;
    MapRoot partition;
} LRGrammarState;

static void LRmakeClosure(LRGrammarState *grammarState);
static void LRpartition(LRGrammarState *grammarState);
static void LRmakeTransition(LRGrammarState *grammarState);
static void extendFollowingTransition(LRGrammarState *grammarState);
static LRGrammarState *LRmakeNextGrammarState(LRGrammarState *grammarState, SymbolDefine left);
static int LRStateListFindNode(LRGrammarState *state);
static LRGrammarState *LRGetGrammarState(My_ArrayList *productionList);
static void LRGrammarStateDestroy(LRGrammarState *grammarState);

static void printClosure(LRGrammarState *grammarState);
static void printLRpartition(LRGrammarState *grammarState);
static void LRGrammarStatePrint(LRGrammarState *grammarState);

static int stateNumCount = 0;
static My_ArrayList *stateList = NULL;

LRGrammarState *LRgrammarStateCreate(My_ArrayList *productions)
{
    LRGrammarState *grammarState = my_malloc(sizeof(LRGrammarState));
    grammarState->printInfo = FALSE;
    grammarState->transitionDone = FALSE;
    grammarState->stateNum = stateNumCount;

    grammarState->productions = productions;
    grammarState->closureSet = ArrayListCreate();
    grammarState->closureSet->equals = (ArrayListDefEquals)productionEquals;

    grammarState->transition = newMap(Map_Number);
    grammarState->partition = newMap(Map_Number);

    ArrayListAddAll(grammarState->closureSet, grammarState->productions);
    return grammarState;
}

void LRincreateStateNum() { stateNumCount++; }

void LRGrammarStatePrint(LRGrammarState *grammarState)
{
    printf("State Number: %d ", grammarState->stateNum);
    for (size_t i = 0; i < grammarState->productions->size; i++)
    {
        productionPrint(ArrayListGetFormPos(grammarState->productions, i));
    }
    printf("\n");
}

void LRcreateTransition(LRGrammarState *grammarState)
{
    if (grammarState->transitionDone == TRUE)
        return;
    grammarState->transitionDone = TRUE;
    printf("\n====make transition=====\n");
    LRGrammarStatePrint(grammarState);

    // ???????????? ?????????????????????????????????
    LRmakeClosure(grammarState);
    // ??????????????????????????????
    LRpartition(grammarState);
    // ??????????????????????????? ??????????????????
    LRmakeTransition(grammarState);
    
    grammarState->printInfo = TRUE;
}

void LRmakeClosure(LRGrammarState *grammarState)
{
    Stack *prductionStack = new_stack();
    for (size_t i = 0; i < grammarState->productions->size; i++)
    {
        sPointPush(prductionStack, ArrayListGetFormPos(grammarState->productions, i));
    }
    while (stacksize(prductionStack) > 0)
    {
        LRProduction *production = spop(prductionStack);
        int symbol = productionGetDotSymbol(production);
        // productionList
        My_ArrayList *closures = getProduction(symbol);
        for (size_t i = 0; closures != NULL && i < closures->size; i++)
        {
            LRProduction *p = ArrayListGetFormPos(closures, i);
            if (ArrayListFindNode(grammarState->closureSet, p) < 0)
            {
                ArrayListPush(grammarState->closureSet, p);
                sPointPush(prductionStack, p);
            }
        }
    }

    printClosure(grammarState);
}

void printClosure(LRGrammarState *grammarState)
{
    if (grammarState->printInfo == TRUE)
        return;
    printf("ClosueSet is: ");
    for (size_t i = 0; i < grammarState->closureSet->size; i++)
    {
        LRProduction *production = ArrayListGetFormPos(grammarState->closureSet, i);
        productionPrint(production);
    }
    printf("\n");
}

void LRpartition(LRGrammarState *grammarState)
{
    for (size_t i = 0; i < grammarState->closureSet->size; i++)
    {
        LRProduction *production = ArrayListGetFormPos(grammarState->closureSet, i);
        SymbolDefine symbol = productionGetDotSymbol(production);
        if (symbol == UNKNOWN_SYMBOL)
            continue;
        // ??????symbol????????????????????????
        My_ArrayList *productionList = MapGetNumNode(grammarState->partition, symbol);
        if (productionList == NULL)
        {
            productionList = ArrayListCreate();
            productionList->equals = (ArrayListDefEquals)productionEquals;
            MapPutNumNode(grammarState->partition, symbol, productionList);
        }
        // ???????????????????????????????????????????????????
        if (ArrayListFindNode(productionList, production) < 0)
            ArrayListPush(productionList, production);
    }
    printLRpartition(grammarState);
}

void printLRpartition(LRGrammarState *grammarState)
{
    if (grammarState->printInfo == TRUE)
        return;
    My_Iterator *itor = newMapIterator(grammarState->partition);
    while (has_itor_next(itor))
    {
        RbNodeP p = get_itor_next(itor);
        printf("partition for symbol: %s ", getSymbolStr(p->key.n));
        My_ArrayList *productionList = p->value;
        for (size_t i = 0; i < productionList->size; i++)
        {
            LRProduction *production = ArrayListGetFormPos(productionList, i);
            productionPrint(production);
        }
    }
    my_iterator_free(itor);
    printf("\n");
}

void LRmakeTransition(LRGrammarState *grammarState)
{
    My_Iterator *itor = newMapIterator(grammarState->partition);

    while (has_itor_next(itor))
    {
        RbNodeP p = get_itor_next(itor);
        SymbolDefine symbol = p->key.n;
        printf("\n====begin print transition info ===++");
        // ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
        LRGrammarState *nextState = LRmakeNextGrammarState(grammarState, symbol);
        MapPutNumNode(grammarState->transition, symbol, nextState);
        printf("from state %d to state %d on %s", grammarState->stateNum, nextState->stateNum, getSymbolStr(symbol));
        printf("----State %d ------", nextState->stateNum);
        LRGrammarStatePrint(grammarState);
    }

    my_iterator_free(itor);
    // ?????????????????????????????????????????????
    extendFollowingTransition(grammarState);
    printf("\n");
}

LRGrammarState *LRmakeNextGrammarState(LRGrammarState *grammarState, SymbolDefine left)
{
    My_ArrayList *productionList = MapGetNumNode(grammarState->partition, left);
    My_ArrayList *newStateProductionList = ArrayListCreate();
    newStateProductionList->equals = (ArrayListDefEquals)productionEquals;
    // ????????????????????? ????????????????????????????????????????????????
    for (size_t i = 0; i < productionList->size; i++)
    {
        LRProduction *production = ArrayListGetFormPos(productionList, i);
        // ???????????? ????????? ?????????????????????
        ArrayListPush(newStateProductionList, productionDotForward(production));
    }
    return LRGetGrammarState(newStateProductionList);
}
/**
 * @brief ????????????????????????????????????????????????
 * 
 */
void extendFollowingTransition(LRGrammarState *grammarState)
{
    My_Iterator *itor = newMapIterator(grammarState->transition);
    while (has_itor_next(itor))
    {
        RbNodeP p = get_itor_next(itor);
        LRGrammarState *newGrammar = p->value;
        // ??????????????????????????????????????????
        if (newGrammar->transitionDone == FALSE)
            LRcreateTransition(newGrammar);
    }
    my_iterator_free(itor);
}

BOOL LRGrammarStateEquals(LRGrammarState *grammarState, LRGrammarState *refGrammarState)
{
    return ArrayListEquals(grammarState->productions, refGrammarState->productions);
}

LRGrammarState *LRGetGrammarState(My_ArrayList *productionList)
{
    LRGrammarState *state = LRgrammarStateCreate(productionList);

    int index = LRStateListFindNode(state);
    if (index < 0)
    {
        ArrayListPush(stateList, state);
        LRincreateStateNum();
        return state;
    }
    LRGrammarStateDestroy(state);
    return ArrayListGetFormPos(stateList, index);
}

int LRStateListFindNode(LRGrammarState *state)
{
    for (int i = 0; i < stateList->size; i++)
    {
        LRGrammarState *cur = ArrayListGetFormPos(stateList, i);
        if (LRGrammarStateEquals(cur, state) == TRUE)
            return i;
    }
    return -1;
}

void LRGrammarStateDestroy(LRGrammarState *grammarState)
{
    ArrayListDestroy(grammarState->closureSet);
    map_destory(grammarState->transition, NULL);
    map_destory(grammarState->partition, NULL);
    my_free(grammarState);
}