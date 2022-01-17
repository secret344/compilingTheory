#include "LRproduction.h"

LRProduction *productionCreate(int left, int dot, My_ArrayList *right)
{
    LRProduction *production = my_malloc(sizeof(LRProduction));
    production->left = left;
    production->right = right;
    if (dot >= right->size)
        dot = right->size;
    production->dotPos = dot;
    return production;
}

LRProduction *productionDotForward(LRProduction *production)
{
    return productionCreate(production->left, production->dotPos + 1, production->right);
}

BOOL productionEquals(LRProduction *production, LRProduction *refProduction)
{
    if (production->left != refProduction->left)
        return FALSE;
    if (ArrayListEquals(production->right, refProduction->right) == FALSE)
        return FALSE;
    if (production->dotPos != refProduction->dotPos)
        return FALSE;
    return TRUE;
}

int productionGetDotSymbol(LRProduction *production)
{
    if (production->dotPos >= production->right)
        return UNKNOWN_SYMBOL;
    return ArrayListGetFormPos(production->right, production->dotPos);
}

void productionPrint(LRProduction *production)
{
    printf("production %s -> ", getSymbolStr(production->left));
    for (size_t i = 0; i < production->right->size; i++)
    {
        if (i == production->dotPos)
        {
            production->printDot = TRUE;
            printf(".");
        }
        printf("%s ", getSymbolStr(ArrayListGetFormPos(production->right, i)));
    }
    if (production->printDot == FALSE)
        printf(".");
    printf("\n");
}