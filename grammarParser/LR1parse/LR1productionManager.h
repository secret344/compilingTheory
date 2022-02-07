#ifndef _LR1_PRODUCTION_MANAGER_
#define _LR1_PRODUCTION_MANAGER_

#include "LR1production.h"
#include "my_map.h"
#include "LR1FirstSetBuilder.h"

void LR1initProductions();
// void printAllProductions();
My_ArrayList *LR1getProduction(SymbolDefine left);
#endif