#include "LR1production.h"
static BOOL productionEquals(LR1Production *production, LR1Production *refProduction);
static int lookAheadSetComparing(LR1Production *production, LR1Production *refProduction);

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
 * @brief 获取 前进 一位的产生式
 * 
 * @param production 
 * @return LR1Production* 
 */
LR1Production *LR1productionNextDotForward(LR1Production *production)
{
    LR1Production *newProduction = LR1productionCreate(production->left, production->dotPos + 1, production->right);
    ArrayListPop(newProduction->lookAhead);
    // 设置展望符
    for (size_t i = 0; i < production->lookAhead->size; i++)
        ArrayListPush(newProduction->lookAhead, ArrayListGetFormPos(production->lookAhead, i));

    return newProduction;
}

LR1Production *LR1productionCloneSelf(LR1Production *production)
{
    LR1Production *newProduction = LR1productionCreate(production->left, production->dotPos, production->right);
    // 去掉默认地 EOI
    ArrayListPop(newProduction->lookAhead);
    // 设置展望符
    for (size_t i = 0; i < production->lookAhead->size; i++)
        ArrayListPush(newProduction->lookAhead, ArrayListGetFormPos(production->lookAhead, i));

    return newProduction;
}
/**
 * @brief 求firstSet与C的并集 
 * 求展望符集合
 * @param production 
 * @return My_ArrayList* 
 */
My_ArrayList *LR1ProductionFirstMergetC(LR1Production *production)
{
    My_ArrayList *result = ArrayListCreate();
    ArrayListAddAll(result, production->lookAhead);
    for (size_t i = production->dotPos + 1; i < production->right->size; i++)
    {
        SymbolDefine sign = ArrayListGetFormPos(production->right, i);
        My_ArrayList *firstSet = LR1getFirstSet(sign);

        for (size_t i = 0; i < firstSet->size; i++)
        {
            SymbolDefine sign = ArrayListGetFormPos(firstSet, i);
            if (ArrayListFindNode(result, sign) < 0)
                ArrayListPush(result, sign);
        }

        // 非nullable 终止循环
        if (LR1isNullable(sign) == FALSE)
            break;
    }
    return result;
}

/**
 * @brief 获取当前 . 所在的文法符号
 * 
 * @param production 
 * @return int 
 */
SymbolDefine LR1productionGetDotSymbol(LR1Production *production)
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
    if (productionEquals(production, refProduction) == TRUE && lookAheadSetComparing(production, refProduction) == COMPARE_EQ)
        return TRUE;
    return FALSE;
}

/**
 * @brief 判断 production 是否被 refProduction  覆盖(LookAhead集合)
 * 
 * @param production 
 * @param refProduction 
 * @return BOOL 
 */
BOOL LR1productionCoverUp(LR1Production *production, LR1Production *refProduction)
{
    if (productionEquals(production, refProduction) == TRUE && lookAheadSetComparing(production, refProduction) == 1)
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
 * @brief 对比展望符  大于1 不等/小于-1 等于COMPARE_EQ(0) （暂定）
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
        return COMPARE_EQ;
    else
        return -1;
}