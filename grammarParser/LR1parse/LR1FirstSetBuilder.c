#include "LR1FirstSetBuilder.h"

static MapRoot symbolMap = NULL;
static My_ArrayList *symbolList = NULL;
// 初始化计算first集合所需要的产生式数据结构
void LR1runFirstSets(MapRoot symbolMap, My_ArrayList *symbolList)
{
    symbolMap = symbolMap;
    symbolList = symbolList;
}