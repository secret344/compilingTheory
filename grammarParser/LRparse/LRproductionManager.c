#include "LRproductionManager.h"
static My_ArrayList *getProductionRight(int *arr, int size);
static void addProduction(LRProduction *production);

static MapRoot productionMap = NULL;

void LRinitProductions()
{
    My_ArrayList *right = NULL;
    //s -> e
    right = getProductionRight((int[1]){EXPR}, 1);
    LRProduction *production = productionCreate(STMT, 0, right);
    addProduction(production);
    //e -> e + t
    right = getProductionRight((int[3]){EXPR, PLUS, TERM}, 3);
    production = productionCreate(EXPR, 0, right);
    addProduction(production);
    //e -> t
    right = getProductionRight((int[1]){TERM}, 1);
    production = productionCreate(EXPR, 0, right);
    addProduction(production);
    //t -> t * f
    right = getProductionRight((int[3]){TERM, TIMES, FACTOR}, 3);
    production = productionCreate(TERM, 0, right);
    addProduction(production);
    //t -> f
    right = getProductionRight((int[1]){FACTOR}, 1);
    production = productionCreate(TERM, 0, right);
    addProduction(production);
    //f -> ( e )
    right = getProductionRight((int[3]){LP, EXPR, RP}, 3);
    production = productionCreate(FACTOR, 0, right);
    addProduction(production);
    //f->NUM
    right = getProductionRight((int[1]){NUM_OR_ID}, 1);
    production = productionCreate(FACTOR, 0, right);
    addProduction(production);
}

My_ArrayList *getProductionRight(int *arr, int size)
{
    My_ArrayList *right = ArrayListCreate();
    for (size_t i = 0; i < size; i++)
    {
        ArrayListPush(right, arr[i]);
    }
    return right;
}

void addProduction(LRProduction *production)
{
    if (productionMap == NULL)
        productionMap = newMap(Map_Number);
    My_ArrayList *productionList = MapGetNumNode(productionMap, production->left);
    if (productionList == NULL)
    {
        productionList = ArrayListCreate();
        MapPutNumNode(productionMap, production->left, productionList);
    }
    if (ArrayListFindNode(productionList, production) < 0)
        ArrayListPush(productionList, production);
}

void printAllProductions()
{
    My_Iterator *itor = newMapIterator(productionMap);
    while (has_itor_next(itor))
    {
        // TODO MAPIterator
        RbNodeP node = get_itor_next(itor);
        My_ArrayList *productionList = node->value;
        for (size_t i = 0; i < productionList->size; i++)
        {
            productionPrint(ArrayListGetFormPos(productionList, i));
            printf("\n");
        }
    }
    my_iterator_free(itor);
}