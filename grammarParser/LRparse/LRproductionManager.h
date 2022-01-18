#ifndef _LR_PRODUCTION_MANAGER_
#define _LR_PRODUCTION_MANAGER_

#include "LRproduction.h"
#include "my_map.h"

void LRinitProductions();
void printAllProductions();
My_ArrayList *getProduction(SymbolDefine left);
#endif