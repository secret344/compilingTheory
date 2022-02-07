#include "LRGrammarStateManager.h"
#include "LRGrammarState.c"

void LRBuildTransitionStateMachine()
{
    stateList = ArrayListCreate();
    LRGrammarState *state = LRGetGrammarState(getProduction(STMT));
    LRcreateTransition(state);
}
