#ifndef _LR1_FIRST_SET_BUILDER_
#define _LR1_FIRST_SET_BUILDER_

#include "my_map.h"
#include "my_ArrayList.h"
#include "my_symbol.h"

void LR1runFirstSets(MapRoot symbolMap, My_ArrayList *symbolList);
My_ArrayList *LR1getFirstSet(SymbolDefine symbol);
BOOL LR1isNullable(SymbolDefine symbol);
BOOL LR1isSymbolTerminals(SymbolDefine symbol);
#endif