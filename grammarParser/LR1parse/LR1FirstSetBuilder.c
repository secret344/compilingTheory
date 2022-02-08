#include "LR1FirstSetBuilder.h"

static void LR1SymbolAddFirstSet(MySymbol *symbol);
static BOOL isSymbolTerminals(SymbolDefine symbol);

static MapRoot symbolMap = NULL;
static My_ArrayList *symbolList = NULL;

static BOOL runFirstSetPass = TRUE;
// 初始化计算first集合所需要的产生式数据结构
void LR1runFirstSets(MapRoot symbolMap, My_ArrayList *symbolList)
{
    symbolMap = symbolMap;
    symbolList = symbolList;

    while (runFirstSetPass == TRUE)
    {
        runFirstSetPass = FALSE;
        for (size_t i = 0; i < symbolList->size; i++)
        {
            MySymbol *symbol = ArrayListGetFormPos(symbolList, i);
        }
    }
}

void LR1SymbolAddFirstSet(MySymbol *symbol)
{
    if (isSymbolTerminals(symbol->value) == TRUE)
        return;
    My_ArrayList *symbolProductions = symbol->productions;
    for (size_t i = 0; i < symbolProductions->size; i++)
    {
        My_ArrayList *right = ArrayListGetFormPos(symbolProductions, i);
        SymbolDefine curSymbolSign = ArrayListGetFormPos(right, 0);
        if (isSymbolTerminals(curSymbolSign) == TRUE && stackPointerInclude(symbol->firstSet, curSymbolSign) == FALSE)
        {
            // 首位非终结符 切当前symbol不存在该字符
            runFirstSetPass = TRUE;
            sIntPush(symbol->firstSet, curSymbolSign);
        }
        else if (isSymbolTerminals(curSymbolSign) == FALSE)
        {
            // 非终结符
            MySymbol *curSymbol = NULL;
            int pos = 0;
            do
            {
                curSymbol = MapGetNumNode(symbolMap, ArrayListGetFormPos(right, pos));
                My_Iterator *itor = newStackIterator(curSymbol->firstSet);
                while (has_itor_next(itor))
                {
                    SymbolDefine curSymbolSign = get_itor_next(itor);
                    if (stackPointerInclude(symbol->firstSet, curSymbolSign) == FALSE)
                    {
                        runFirstSetPass = TRUE;
                        sIntPush(symbol->firstSet, curSymbolSign);
                    }
                }

                my_iterator_free(itor);
                pos++;
            } while (pos < right->size && curSymbol->isNullable == TRUE);
        }
    }
}

BOOL isSymbolTerminals(SymbolDefine symbol)
{
    return symbol < 256 ? TRUE : FALSE;
}
/**
 * @brief 获取firstSet 返回一个数组
 * 本身是栈结构 转换成数组 
 * @param symbol 
 * @return My_ArrayList* 
 */
My_ArrayList *LR1getFirstSet(SymbolDefine symbol)
{
    MySymbol *s = MapGetNumNode(symbolMap, symbol);
    return s != NULL ? s->firstSet : NULL;
}

BOOL LR1isNullable(SymbolDefine symbol)
{
    MySymbol *s = MapGetNumNode(symbolMap, symbol);
    return s == NULL ? FALSE : s->isNullable;
}