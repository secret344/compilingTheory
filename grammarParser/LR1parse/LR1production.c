#include "LR1production.h"
static BOOL productionEquals(LR1Production *production, LR1Production *refProduction);
LR1Production *LR1productionCreate(int left, int dot, My_ArrayList *right)
{
    LR1Production *production = my_malloc(sizeof(LR1Production));
    production->left = left;
    production->right = right;
    if (dot >= right->size)
        dot = right->size;
    production->dotPos = dot;
    production->lookAhead = ArrayListCreate();
    ArrayListPush(production->lookAhead, EOI);
    return production;
}
/**
 * @brief 获取前进一位的产生式
 * 
 * @param production 
 * @return LR1Production* 
 */
LR1Production *LR1productionDotForward(LR1Production *production)
{
    LR1Production *newProduction = LR1productionCreate(production->left, production->dotPos + 1, production->right);
    // 设置展望符
    for (size_t i = 0; i < production->lookAhead->size; i++)
        ArrayListPush(newProduction->lookAhead, ArrayListGetFormPos(production->lookAhead, i));

    return newProduction;
}

LR1Production *LR1productionCloneSelf(LR1Production *production)
{
    LR1Production *newProduction = LR1productionCreate(production->left, production->dotPos, production->right);
    // 设置展望符
    for (size_t i = 0; i < production->lookAhead->size; i++)
        ArrayListPush(newProduction->lookAhead, ArrayListGetFormPos(production->lookAhead, i));

    return newProduction;
}

/**
 * @brief 获取当前 . 所在的文法符号
 * 
 * @param production 
 * @return int 
 */
int productionGetDotSymbol(LR1Production *production)
{
    if (production->dotPos >= production->right->size)
        return UNKNOWN_SYMBOL;
    return ArrayListGetFormPos(production->right, production->dotPos);
}

/**
 * @brief 判断产生式是否相等
 * 
 * @param production 
 * @param refProduction 
 * @return BOOL 
 */
BOOL LR1productionEquals(LR1Production *production, LR1Production *refProduction)
{
    if (productionEquals(production, refProduction) == TRUE && lookAheadSetComparing(production, refProduction) == TRUE)
        return TRUE;
    return FALSE;
}

BOOL productionEquals(LR1Production *production, LR1Production *refProduction)
{
    if (production->left != refProduction->left)
        return FALSE;
    if (ArrayListEquals(production->right, refProduction->right) == FALSE)
        return FALSE;
    if (production->dotPos != refProduction->dotPos)
        return FALSE;
    return TRUE;
}
/**
 * @brief 对比展望符  大于1 小于-1 等于0 不等-1 （暂定）
 * 
 * @param production 
 * @param refProduction 
 * @return int 
 */
int lookAheadSetComparing(LR1Production *production, LR1Production *refProduction)
{
    if (production->lookAhead->size > refProduction->lookAhead->size)
        return 1;
    if (production->lookAhead->size < refProduction->lookAhead->size)
        return -1;
    if (ArrayListEquals(production->lookAhead, refProduction->lookAhead))
        return 0;
    else
        return -1;
}