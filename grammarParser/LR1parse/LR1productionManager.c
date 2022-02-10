#include "LR1productionManager.h"

static My_ArrayList *getProductionRight(int *arr, int size);
static void addProduction(LR1Production *production);

static MapRoot productionMap = NULL;

void LR1initProductions()
{
    // 为方便计算first集合初始化数据结构
    MapRoot symbolMap = newMap(Map_Number);
    My_ArrayList *symbolList = ArrayListCreate();

    My_ArrayList *symbolProductions = NULL; // 为计算first集合方便 将相同符号产生式放在数组中
    My_ArrayList *right = NULL;
    // s -> e
    right = getProductionRight((int[1]){EXPR}, 1);
    symbolProductions = ArrayListCreate();
    LR1Production *production = LR1productionCreate(STMT, 0, right);
    addProduction(production);

    ArrayListPush(symbolProductions, right);
    MySymbol *symbol = newSymbol(STMT, FALSE, symbolProductions);
    ArrayListPush(symbolList, symbol);
    MapPutNumNode(symbolMap, STMT, &*symbol);

    // e -> e + t
    symbolProductions = ArrayListCreate();
    right = getProductionRight((int[3]){EXPR, PLUS, TERM}, 3);
    production = LR1productionCreate(EXPR, 0, right);
    addProduction(production);

    ArrayListPush(symbolProductions, right);
    // e -> t
    right = getProductionRight((int[1]){TERM}, 1);
    production = LR1productionCreate(EXPR, 0, right);
    addProduction(production);

    ArrayListPush(symbolProductions, right);
    symbol = newSymbol(EXPR, FALSE, symbolProductions);
    MapPutNumNode(symbolMap, EXPR, &*symbol);
    ArrayListPush(symbolList, symbol);

    // t -> t * f
    symbolProductions = ArrayListCreate();
    right = getProductionRight((int[3]){TERM, TIMES, FACTOR}, 3);
    production = LR1productionCreate(TERM, 0, right);
    addProduction(production);

    ArrayListPush(symbolProductions, right);
    // t -> f
    right = getProductionRight((int[1]){FACTOR}, 1);
    production = LR1productionCreate(TERM, 0, right);
    addProduction(production);

    ArrayListPush(symbolProductions, right);
    symbol = newSymbol(TERM, FALSE, symbolProductions);
    MapPutNumNode(symbolMap, TERM, symbol);
    ArrayListPush(symbolList, symbol);
    // f -> ( e )
    symbolProductions = ArrayListCreate();
    right = getProductionRight((int[3]){LP, EXPR, RP}, 3);
    production = LR1productionCreate(FACTOR, 0, right);
    addProduction(production);

    ArrayListPush(symbolProductions, right);
    // f->NUM
    right = getProductionRight((int[1]){NUM_OR_ID}, 1);
    production = LR1productionCreate(FACTOR, 0, right);
    addProduction(production);

    ArrayListPush(symbolProductions, right);
    symbol = newSymbol(FACTOR, FALSE, symbolProductions);
    MapPutNumNode(symbolMap, FACTOR, symbol);
    ArrayListPush(symbolList, symbol);

    // 终结符
    // ;
    // MySymbol *semi = newSymbol(SEMI, FALSE, NULL);
    // MapPutNumNode(symbolMap, SEMI, semi);
    // ArrayListPush(symbolList, semi);
    // EOI
    MySymbol *eoi = newSymbol(EOI, FALSE, NULL);
    MapPutNumNode(symbolMap, EOI, eoi);
    ArrayListPush(symbolList, eoi);
    // +
    MySymbol *plus = newSymbol(PLUS, FALSE, NULL);
    MapPutNumNode(symbolMap, PLUS, plus);
    ArrayListPush(symbolList, plus);
    // *
    MySymbol *times = newSymbol(TIMES, FALSE, NULL);
    MapPutNumNode(symbolMap, TIMES, times);
    ArrayListPush(symbolList, times);
    // lp (
    MySymbol *lp = newSymbol(LP, FALSE, NULL);
    MapPutNumNode(symbolMap, LP, lp);
    ArrayListPush(symbolList, lp);
    // rp )
    MySymbol *rp = newSymbol(RP, FALSE, NULL);
    MapPutNumNode(symbolMap, RP, rp);
    ArrayListPush(symbolList, rp);
    // num_or_id 数字或者id
    MySymbol *num_or_id = newSymbol(NUM_OR_ID, FALSE, NULL);
    MapPutNumNode(symbolMap, NUM_OR_ID, num_or_id);
    ArrayListPush(symbolList, num_or_id);

    // 进行firstSet计算
    LR1runFirstSets(symbolMap, symbolList);
}

My_ArrayList *getProductionRight(int *arr, int size)
{
    My_ArrayList *right = ArrayListCreate();

    for (size_t i = 0; i < size; i++)
        ArrayListPush(right, arr[i]);

    return right;
}

void addProduction(LR1Production *production)
{
    if (productionMap == NULL)
        productionMap = newMap(Map_Number);

    My_ArrayList *productionList = MapGetNumNode(productionMap, production->left);

    if (productionList == NULL)
    {
        productionList = ArrayListCreate();
        // 修改默认的对比方法
        productionList->equals = (ArrayListDefEquals)LR1productionEquals;
        MapPutNumNode(productionMap, production->left, productionList);
    }

    if (ArrayListFindNode(productionList, production) < 0)
        ArrayListPush(productionList, production);
}

/**
 * @brief 获取对应符号相应的产生式数组
 *
 * @param left
 * @return My_ArrayList*
 */
My_ArrayList *LR1getProduction(SymbolDefine left)
{
    return MapGetNumNode(productionMap, left);
}