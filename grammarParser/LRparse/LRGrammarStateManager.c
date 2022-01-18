#include "LRGrammarStateManager.h"
#include "LRGrammarState.c"
static int LRStateListFindNode(LRGrammarState *state);
static My_ArrayList *stateList = NULL;
void LRBuildTransitionStateMachine()
{
    stateList = ArrayListCreate();
    LRGrammarState *state = LRGetGrammarState(getProduction(STMT));
}

LRGrammarState *LRGetGrammarState(My_ArrayList *productionList)
{
    LRGrammarState *state = LRgrammarStateCreate(productionList);

    int index = LRStateListFindNode(productionList);
    if (index < 0)
    {
        ArrayListPush(stateList, state);
        LRincreateStateNum();
        return state;
    }
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