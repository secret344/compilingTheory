#include "LR1FirstSetBuilder.h"

static void LR1SymbolAddFirstSet(MySymbol *symbol);

static MapRoot LR1SymbolMap = NULL;
static My_ArrayList *LR1SymbolList = NULL;
static void printFirstSet(MySymbol *symbol);
static void printAllFirstSet();
static BOOL LR1runFirstSetPass = TRUE;
//  STMT : {  LEFT_PARENT  NUM_OR_ID  }
//  EXPR : {  NUM_OR_ID  LEFT_PARENT  }
//  TERM : {  LEFT_PARENT  NUM_OR_ID  }
//  FACTOR : {  NUM_OR_ID  LEFT_PARENT  }
//  PLUS : {  PLUS  }
//  TIMES : {  TIMES  }
//  LEFT_PARENT : {  LEFT_PARENT  }
//  RIGHT_PARENT : {  RIGHT_PARENT  }
//  NUM_OR_ID : {  NUM_OR_ID  }
// 初始化计算first集合所需要的产生式数据结构
void LR1runFirstSets(MapRoot symbolMap, My_ArrayList *symbolList)
{
    LR1SymbolMap = symbolMap;
    LR1SymbolList = symbolList;
    while (LR1runFirstSetPass == TRUE)
    {
        LR1runFirstSetPass = FALSE;
        for (size_t i = 0; i < LR1SymbolList->size; i++)
        {
            MySymbol *symbol = ArrayListGetFormPos(LR1SymbolList, i);
            LR1SymbolAddFirstSet(symbol);
        }
    }
    printAllFirstSet();
}

void printAllFirstSet()
{
    printf("\n-------firstSet--------\n");
    for (size_t i = 0; i < LR1SymbolList->size; i++)
    {
        printFirstSet(ArrayListGetFormPos(LR1SymbolList, i));
        printf("\n");
    }
    printf("\n-----------------------\n");
}

void printFirstSet(MySymbol *symbol)
{

    printf(" %s : { ", getSymbolStr(symbol->value));
    My_Iterator *itor = newStackIterator(symbol->firstSet);
    while (has_itor_next(itor))
    {
        SymbolDefine symbol = get_itor_next(itor);
        printf(" %s ", getSymbolStr(symbol));
    }
    my_iterator_free(itor);
    printf(" } ");
}

void LR1SymbolAddFirstSet(MySymbol *symbol)
{
    if (LR1isSymbolTerminals(symbol->value) == TRUE)
        return;
    My_ArrayList *symbolProductions = symbol->productions;
    for (size_t i = 0; i < symbolProductions->size; i++)
    {
        My_ArrayList *right = ArrayListGetFormPos(symbolProductions, i);
        SymbolDefine curSymbolSign = ArrayListGetFormPos(right, 0);

        if (LR1isSymbolTerminals(curSymbolSign) == TRUE && stackPointerInclude(symbol->firstSet, curSymbolSign) == FALSE)
        {
            // 首位非终结符 切当前symbol不存在该字符
            LR1runFirstSetPass = TRUE;
            sIntPush(symbol->firstSet, curSymbolSign);
        }
        else if (LR1isSymbolTerminals(curSymbolSign) == FALSE)
        {
            // 非终结符
            MySymbol *curSymbol = NULL;
            int pos = 0;
            do
            {
                curSymbol = MapGetNumNode(LR1SymbolMap, ArrayListGetFormPos(right, pos));
                My_Iterator *itor = newStackIterator(curSymbol->firstSet);
                while (has_itor_next(itor))
                {
                    curSymbolSign = get_itor_next(itor);
                    if (stackPointerInclude(symbol->firstSet, curSymbolSign) == FALSE)
                    {
                        LR1runFirstSetPass = TRUE;
                        sIntPush(symbol->firstSet, curSymbolSign);
                    }
                }

                my_iterator_free(itor);
                pos++;
            } while (pos < right->size && curSymbol->isNullable == TRUE);
        }
    }
}

BOOL LR1isSymbolTerminals(SymbolDefine symbol)
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
    MySymbol *s = MapGetNumNode(LR1SymbolMap, symbol);
    printf("\n %s firstSet: ", getSymbolStr(symbol));
    if (s == NULL)
        return NULL;
    My_ArrayList *firstSetArr = ArrayListCreate();
    My_Iterator *itor = newStackIterator(s->firstSet);
    while (has_itor_next(itor))
    {
        SymbolDefine symbol = get_itor_next(itor);
        printf(" %s ", getSymbolStr(symbol));
        ArrayListPush(firstSetArr, symbol);
    }
    my_iterator_free(itor);
    printf("\n");
    return firstSetArr;
}

BOOL LR1isNullable(SymbolDefine symbol)
{
    MySymbol *s = MapGetNumNode(LR1SymbolMap, symbol);
    return s == NULL ? FALSE : s->isNullable;
}