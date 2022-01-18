#include "bool.h"
#include "my_ArrayList.h"
#include "my_map.h"
#include "LRproduction.h"

static stateNumCount = 0;

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

LRGrammarState *LRgrammarStateCreate(My_ArrayList *productions)
{
    LRGrammarState *grammarState = my_malloc(sizeof(LRGrammarState));
    grammarState->printInfo = FALSE;
    grammarState->transitionDone = FALSE;
    grammarState->stateNum = stateNumCount;

    grammarState->productions = productions;
    grammarState->closureSet = ArrayListCreate();

    grammarState->transition = newMap(Map_Number);
    grammarState->partition = newMap(Map_Number);

    ArrayListAddAll(grammarState->closureSet, grammarState->productions);
}

void LRincreateStateNum() { stateNumCount++; }

BOOL LRGrammarStateEquals(LRGrammarState *grammarState, LRGrammarState *refGrammarState)
{
    return ArrayListEquals(grammarState->productions, refGrammarState->productions);
}