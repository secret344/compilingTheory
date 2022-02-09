#include "LR1compiler.h"

void LR1initParser()
{
    LR1initProductions();
    LR1BuildTransitionStateMachine();
}