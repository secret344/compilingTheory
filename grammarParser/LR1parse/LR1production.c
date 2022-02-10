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
    LR1AddProductionLookAhead(newProduction, production->lookAhead);
    return newProduction;
}

LR1Production *LR1productionCloneSelf(LR1Production *production)
{
    LR1Production *newProduction = LR1productionCreate(production->left, production->dotPos, production->right);
    LR1AddProductionLookAhead(newProduction, production->lookAhead);
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
    My_ArrayList *sequela = ArrayListCreate();
    My_ArrayList *result = ArrayListCreate();
    // [A -> α.Bβ , a]
    // 等价项目：
    // [B -> .γ , b]
    // 当β可为空时 a 是 b 的后继符
    // b = first(βa)

    // 移入 β
    for (size_t i = production->dotPos + 1; i < production->right->size; i++)
        ArrayListPush(sequela, ArrayListGetFormPos(production->right, i));
    ArrayListAddAll(sequela, production->lookAhead); // 移入 a 因为 集合a 必然为终结符集合 

    for (size_t i = 0; i < sequela->size; i++)
    {
        SymbolDefine sign = ArrayListGetFormPos(sequela, i);
        My_ArrayList *firstSet = LR1getFirstSet(sign);

        for (size_t i = 0; i < firstSet->size; i++)
        {
            SymbolDefine signC = ArrayListGetFormPos(firstSet, i);
            if (ArrayListFindNode(result, signC) < 0)
                ArrayListPush(result, signC);
        }
        ArrayListDestroy(firstSet);
        // 非nullable 终止循环 终结符都是非nullable
        if (LR1isNullable(sign) == FALSE)
            break;
    }
    ArrayListDestroy(sequela);
    return result;
}

void LR1AddProductionLookAhead(LR1Production *production, My_ArrayList *array)
{
    for (size_t i = 0; i < array->size; i++)
    {
        SymbolDefine symbol = ArrayListGetFormPos(array, i);
        if (ArrayListFindNode(production->lookAhead, symbol) < 0)
            ArrayListPush(production->lookAhead, symbol);
    }
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
    if (productionEquals(production, refProduction) == TRUE && lookAheadSetComparing(production, refProduction) > 0)
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
 * @brief 对比展望符  大于1 不等/小于0 等于COMPARE_EQ(-1) （暂定）
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
        return 0;
    if (ArrayListEquals(production->lookAhead, refProduction->lookAhead) == FALSE)
        return 0;
    return COMPARE_EQ;
}

void LR1productionPrint(LR1Production *production)
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

    printf("\n lookAhead: ");
    for (size_t i = 0; i < production->lookAhead->size; i++)
    {
        printf(" %s ", getSymbolStr(ArrayListGetFormPos(production->lookAhead, i)));
    }

    printf("\n");
}