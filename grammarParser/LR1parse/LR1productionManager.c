#include "LR1productionManager.h"

static My_ArrayList *getProductionRight(int *arr, int size);
static void addProduction(LR1Production *production);

static MapRoot productionMap = NULL;

void LR1initProductions()
{
    MapRoot symbolMap = newMap(Map_Number);
    My_ArrayList *symbolList = ArrayListCreate();

    My_ArrayList *symbolList = NULL;
    My_ArrayList *right = NULL;
    //s -> e
    right = getProductionRight((int[1]){EXPR}, 1);

    LR1Production *production = LR1productionCreate(STMT, 0, right);
    MySymbol *symbol = newSymbol(STMT, FALSE, right);
    addProduction(production);
    //e -> e + t
    right = getProductionRight((int[3]){EXPR, PLUS, TERM}, 3);
    production = LR1productionCreate(EXPR, 0, right);
    MySymbol *symbol = newSymbol(STMT, FALSE, right);
    addProduction(production);
    //e -> t
    right = getProductionRight((int[1]){TERM}, 1);
    production = LR1productionCreate(EXPR, 0, right);
    MySymbol *symbol = newSymbol(STMT, FALSE, right);
    addProduction(production);
    //t -> t * f
    right = getProductionRight((int[3]){TERM, TIMES, FACTOR}, 3);
    production = LR1productionCreate(TERM, 0, right);
    MySymbol *symbol = newSymbol(STMT, FALSE, right);
    addProduction(production);
    //t -> f
    right = getProductionRight((int[1]){FACTOR}, 1);
    production = LR1productionCreate(TERM, 0, right);
    MySymbol *symbol = newSymbol(STMT, FALSE, right);
    addProduction(production);
    //f -> ( e )
    right = getProductionRight((int[3]){LP, EXPR, RP}, 3);
    production = LR1productionCreate(FACTOR, 0, right);
    MySymbol *symbol = newSymbol(STMT, FALSE, right);
    addProduction(production);
    //f->NUM
    right = getProductionRight((int[1]){NUM_OR_ID}, 1);
    production = LR1productionCreate(FACTOR, 0, right);
    MySymbol *symbol = newSymbol(STMT, FALSE, right);
    addProduction(production);
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
    if (ArrayListFindNode(productionList, production) == FALSE)
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