#include "parse_table_builder.h"

static void runFirstSets();
static void addSymbolFirstSet(MySymbol *symbol);
static BOOL isSymbolTerminals(SymbolDefine symbol);
static void printFirstSet(MySymbol *symbol);

static void runFollowSets();
static void addSymbolFollowSet(MySymbol *symbol);
static void addSetToFollowSet(MySymbol *symbolBeAdd, Stack *set);
static void printFollowSet(MySymbol *symbol);

static void runSelectionSet();
static void addSymbolSelectionSet(MySymbol *symbol);
static void addSetToSelectionSet(Stack *selectionSet, Stack *set);
static void printSelectionSet(MySymbol *symbol);

static void buildParseTable();
static void initializeParseTable();
static void setParseTable();
static void printfParseTable();

static int **parseTable = NULL;
static int productionCount = 0;

static void parseError();
static Stack *symbolArray = NULL;
static MapRoot symbolMap = NULL;
static BOOL runFirstSetPass = TRUE;
static BOOL runFollowSetPass = TRUE;

void parseError()
{
    printf("PDA parse error");
    exit(1);
}

void initProductions()
{
    symbolArray = new_stack();
    symbolMap = newMap(Map_Number);
    // stmt -> expr SEMI
    // expr -> term expr’ | ε
    // expr’ -> PLUS term expr’ |ε
    // term -> factor term’
    // term’ -> TIMES factor term’ |ε
    // factor -> LEFT_PAREN expr RIGHT_PAREN | NUMBER
    //
    // stmt -> expr SEMI
    Stack *productions = new_stack();
    sPointPush(productions, (int[3]){EXPR, SEMI, GRAMMAR_END});
    MySymbol *stmt = newSymbol(STMT, FALSE, productions);
    MapPutNumNode(symbolMap, STMT, stmt);
    sPointPush(symbolArray, stmt);
    // expr -> term expr’ | ε
    productions = new_stack();
    sPointPush(productions, (int[3]){TERM, EXPR_PRIME, GRAMMAR_END});
    sPointPush(productions, (int[1]){GRAMMAR_END});
    MySymbol *expr = newSymbol(EXPR, TRUE, productions);
    MapPutNumNode(symbolMap, EXPR, expr);
    sPointPush(symbolArray, expr);
    // expr’ -> PLUS term expr’ |ε
    productions = new_stack();
    sPointPush(productions, (int[4]){PLUS, TERM, EXPR_PRIME, GRAMMAR_END});
    sPointPush(productions, (int[1]){GRAMMAR_END});
    MySymbol *expr_prime = newSymbol(EXPR_PRIME, TRUE, productions);
    MapPutNumNode(symbolMap, EXPR_PRIME, expr_prime);
    sPointPush(symbolArray, expr_prime);
    // term -> factor term’
    productions = new_stack();
    sPointPush(productions, (int[3]){FACTOR, TERM_PRIME, GRAMMAR_END});
    MySymbol *term = newSymbol(TERM, FALSE, productions);
    MapPutNumNode(symbolMap, TERM, term);
    sPointPush(symbolArray, term);
    // term’ -> TIMES factor term’ |ε
    productions = new_stack();
    sPointPush(productions, (int[4]){TIMES, FACTOR, TERM_PRIME, GRAMMAR_END});
    sPointPush(productions, (int[1]){GRAMMAR_END});
    MySymbol *term_prime = newSymbol(TERM_PRIME, TRUE, productions);
    MapPutNumNode(symbolMap, TERM_PRIME, term_prime);
    sPointPush(symbolArray, term_prime);
    // factor -> LEFT_PAREN expr RIGHT_PAREN | NUMBER
    productions = new_stack();
    sPointPush(productions, (int[4]){LP, EXPR, RP, GRAMMAR_END});
    sPointPush(productions, (int[2]){NUM_OR_ID, GRAMMAR_END});
    MySymbol *factor = newSymbol(FACTOR, FALSE, productions);
    MapPutNumNode(symbolMap, FACTOR, factor);
    sPointPush(symbolArray, factor);
    // 终结符
    // ;
    MySymbol *semi = newSymbol(SEMI, FALSE, NULL);
    MapPutNumNode(symbolMap, SEMI, semi);
    sPointPush(symbolArray, semi);
    // +
    MySymbol *plus = newSymbol(PLUS, FALSE, NULL);
    MapPutNumNode(symbolMap, PLUS, plus);
    sPointPush(symbolArray, plus);
    // *
    MySymbol *times = newSymbol(TIMES, FALSE, NULL);
    MapPutNumNode(symbolMap, TIMES, times);
    sPointPush(symbolArray, times);
    // lp (
    MySymbol *lp = newSymbol(LP, FALSE, NULL);
    MapPutNumNode(symbolMap, LP, lp);
    sPointPush(symbolArray, lp);
    // rp )
    MySymbol *rp = newSymbol(RP, FALSE, NULL);
    MapPutNumNode(symbolMap, RP, rp);
    sPointPush(symbolArray, rp);
    // num_or_id 数字或者id
    MySymbol *num_or_id = newSymbol(NUM_OR_ID, FALSE, NULL);
    MapPutNumNode(symbolMap, NUM_OR_ID, num_or_id);
    sPointPush(symbolArray, num_or_id);
    //
    runFirstSets();
    runFollowSets();
    runSelectionSet();
    buildParseTable();
}

void runFirstSets()
{
    int count = 1;
    while (runFirstSetPass == TRUE)
    {
        printf("%d遍\n-------------------------\n", count++);
        runFirstSetPass = FALSE;
        My_Iterator *itor = newStackIterator(symbolArray);
        while (has_itor_next(itor))
        {
            MySymbol *symbol = get_itor_next(itor);
            addSymbolFirstSet(symbol);
            printFirstSet(symbol);
        }
        my_iterator_free(itor);
    }
}

void addSymbolFirstSet(MySymbol *symbol)
{
    if (isSymbolTerminals(symbol->value) == TRUE)
    {
        return;
    }
    Stack *curProductions = symbol->productions;
    My_Iterator *itor = newStackIterator(curProductions);
    while (has_itor_next(itor))
    {
        int *rightSize = (int *)get_itor_next(itor);
        if (isSymbolTerminals(*rightSize) && stackPointerInclude(symbol->firstSet, *rightSize) == FALSE)
        {
            // 首个字符为终结符，且first集当前不存在该字符
            runFirstSetPass = TRUE;
            sIntPush(symbol->firstSet, *rightSize);
        }
        else if (isSymbolTerminals(*rightSize) == FALSE)
        {
            // 字符为非终结符
            unsigned int offset = 0;
            MySymbol *curSymbol = NULL;
            do
            {
                // 拿到当前非终结符
                curSymbol = MapGetNumNode(symbolMap, *(rightSize + offset));
                // 判断是否已经存在symbol的first集合
                // 如果是非终结符 则 firstset为 NULL isNullable 为 FALSE 结束
                if (StackContainsAll(symbol->firstSet, curSymbol->firstSet) == FALSE)
                {
                    runFirstSetPass = TRUE;
                    My_Iterator *itorCurSymbol = newStackIterator(curSymbol->firstSet);
                    while (has_itor_next(itorCurSymbol))
                    {
                        SymbolDefine sign = get_itor_next(itorCurSymbol);
                        if (stackPointerInclude(symbol->firstSet, sign) == FALSE)
                            sIntPush(symbol->firstSet, sign);
                    }
                    my_iterator_free(itorCurSymbol);
                }
                offset++;
                // 当前非终结符属于nullable,则下一个字符的first集合也属于当前symbol的firstset
            } while (*(rightSize + offset) != GRAMMAR_END && curSymbol->isNullable);
        }
    }
    my_iterator_free(itor);
}

BOOL isSymbolTerminals(SymbolDefine symbol)
{
    return symbol < 256 ? TRUE : FALSE;
}

void runFollowSets()
{
    int count = 1;
    while (runFollowSetPass == TRUE)
    {
        printf("\nrunFollowSets %d 遍----------------------------------\n", count++);
        runFollowSetPass = FALSE;
        My_Iterator *itor = newStackIterator(symbolArray);
        while (has_itor_next(itor))
        {
            MySymbol *symbol = get_itor_next(itor);
            addSymbolFollowSet(symbol);
            printFollowSet(symbol);
        }
        my_iterator_free(itor);
    }
}
void addSymbolFollowSet(MySymbol *symbol)
{
    if (isSymbolTerminals(symbol->value) == TRUE)
        return;
    My_Iterator *productionList = newStackIterator(symbol->productions);
    while (has_itor_next(productionList))
    {
        int *rightSize = get_itor_next(productionList);
        int offset = 0;
        // 前一位非终结符followSet包含后一位的firstSet
        // 后一位若为nullable,则该非终结符 followSet 包含后一位之后的symbol的firstSet
        // 以此类推
        while (*(rightSize + offset) != GRAMMAR_END)
        {
            MySymbol *curSymbol = MapGetNumNode(symbolMap, *(rightSize + offset));
            if (isSymbolTerminals(curSymbol->value) == FALSE)
            {
                int nextPos = offset + 1;
                // 当前非终结符 followSet 包含下一位的firstSet
                while (*(rightSize + nextPos) != GRAMMAR_END)
                {
                    MySymbol *nextSymbol = MapGetNumNode(symbolMap, *(rightSize + nextPos));
                    addSetToFollowSet(curSymbol, nextSymbol->firstSet);
                    // 如果nextSymbol不为 nullable 跳出循环
                    if (nextSymbol->isNullable == FALSE)
                        break;
                    nextPos++;
                }
            }
            offset++;
        }

        int pos = offset - 1;
        // 当前symbol 最右侧 非终结符的followSet包含当前symbol的followSet
        // 若最右侧为 nullable 则最右侧前一位 followSet 也包含当前symbol的followSet
        // 以此类推
        while (pos >= 0)
        {
            MySymbol *curSymbol = MapGetNumNode(symbolMap, *(rightSize + pos));
            if (isSymbolTerminals(curSymbol->value) == FALSE)
                addSetToFollowSet(curSymbol, symbol->followSet);
            // 若不为 nullable 终结符 跳出循环
            if (isSymbolTerminals(curSymbol->value) == TRUE || curSymbol->isNullable == FALSE)
                break;
            pos--;
        }
    }

    my_iterator_free(productionList);
}

void addSetToFollowSet(MySymbol *symbolBeAdd, Stack *set)
{
    if (StackContainsAll(symbolBeAdd->followSet, set) == FALSE)
    {
        My_Iterator *itor = newStackIterator(set);
        while (has_itor_next(itor))
        {
            SymbolDefine symbol = get_itor_next(itor);
            if (stackPointerInclude(symbolBeAdd->followSet, symbol) == FALSE)
            {
                sIntPush(symbolBeAdd->followSet, symbol);
                runFollowSetPass = TRUE;
            }
        }
        my_iterator_free(itor);
    }
}

void printFirstSet(MySymbol *symbol)
{
    if (isSymbolTerminals(symbol->value))
    {
        return;
    }
    Stack *firstSet = symbol->firstSet;
    printf("%s firstSet: {", getSymbolStr(symbol->value));
    My_Iterator *itorFirstSet = newStackIterator(firstSet);
    while (has_itor_next(itorFirstSet))
    {
        SymbolDefine sign = get_itor_next(itorFirstSet);
        printf(" %s ", getSymbolStr(sign));
    }
    printf("}\n");
    my_iterator_free(itorFirstSet);
}

void printFollowSet(MySymbol *symbol)
{
    if (isSymbolTerminals(symbol->value))
    {
        return;
    }
    Stack *followSet = symbol->followSet;
    printf("%s followSet: {", getSymbolStr(symbol->value));
    My_Iterator *itorFollowSet = newStackIterator(followSet);
    while (has_itor_next(itorFollowSet))
    {
        SymbolDefine sign = get_itor_next(itorFollowSet);
        printf(" %s ", getSymbolStr(sign));
    }
    printf("}\n");
    my_iterator_free(itorFollowSet);
}
// select集合
void runSelectionSet()
{
    My_Iterator *itor = newStackIterator(symbolArray);
    while (has_itor_next(itor))
    {
        MySymbol *symbol = get_itor_next(itor);
        addSymbolSelectionSet(symbol);
    }
    my_iterator_free(itor);

    My_Iterator *itor1 = newStackIterator(symbolArray);
    printf("\nrunSelectionSet ----------------------------------\n");
    while (has_itor_next(itor1))
    {
        MySymbol *symbol = get_itor_next(itor1);
        printSelectionSet(symbol);
    }
    my_iterator_free(itor1);
}

void addSymbolSelectionSet(MySymbol *symbol)
{
    if (isSymbolTerminals(symbol) == TRUE)
        return;
    Stack *curProductions = symbol->productions;
    My_Iterator *itorProduction = newStackIterator(curProductions);
    BOOL isNullableProduction = TRUE;
    while (has_itor_next(itorProduction))
    {
        int *rightSize = get_itor_next(itorProduction);
        Stack *selection = new_stack();
        int offset = 0;
        while (*(rightSize + offset) != GRAMMAR_END)
        {
            MySymbol *next = MapGetNumNode(symbolMap, *(rightSize + offset));
            if (next->isNullable == FALSE)
            {
                isNullableProduction = FALSE;
                addSetToSelectionSet(selection, next->firstSet);
                break;
            }

            addSetToSelectionSet(selection, next->firstSet);
            offset++;
        }

        if (isNullableProduction == TRUE)
            addSetToSelectionSet(selection, symbol->followSet);

        sPointPush(symbol->selectionSet, selection);
        isNullableProduction = TRUE;
    }
    my_iterator_free(itorProduction);
}

void addSetToSelectionSet(Stack *selectionSet, Stack *set)
{
    My_Iterator *itor = newStackIterator(set);
    while (has_itor_next(itor))
    {
        SymbolDefine symbol = get_itor_next(itor);
        if (stackPointerInclude(selectionSet, symbol) == FALSE)
            sIntPush(selectionSet, symbol);
    }
    my_iterator_free(itor);
}

void printSelectionSet(MySymbol *symbol)
{
    if (isSymbolTerminals(symbol->value))
    {
        return;
    }
    Stack *selectionSet = symbol->selectionSet;
    printf("%s selectionSet: {", getSymbolStr(symbol->value));
    My_Iterator *itorSelectionSet = newStackIterator(selectionSet);
    while (has_itor_next(itorSelectionSet))
    {
        Stack *selection = get_itor_next(itorSelectionSet);
        My_Iterator *selectionItem = newStackIterator(selection);
        while (has_itor_next(selectionItem))
        {
            SymbolDefine sign = get_itor_next(selectionItem);
            printf(" %s ", getSymbolStr(sign));
        }
        my_iterator_free(selectionItem);
        printf(" ; ");
    }
    printf("}\n");
    my_iterator_free(itorSelectionSet);
}

// buildParseTable
void buildParseTable()
{
    initializeParseTable();
    setParseTable();
    printfParseTable();
}

void initializeParseTable()
{
    parseTable = (int **)my_malloc(sizeof(int *) * NO_TERMINAL_MAXRANGE);
    for (size_t i = 0; i < NO_TERMINAL_MAXRANGE; i++)
    {
        parseTable[i] = (int *)my_malloc(TERMINAL_MAX_RANGE * sizeof(int));
        for (size_t j = 0; j < TERMINAL_MAX_RANGE; j++)
            parseTable[i][j] = GRAMMAR_END;
    }
}

void setParseTable()
{
    Stack *reverSymbolArray = StackReversal(symbolArray);
    My_Iterator *itor = newStackIterator(reverSymbolArray);
    while (has_itor_next(itor))
    {
        MySymbol *symbol = get_itor_next(itor);
        if (isSymbolTerminals(symbol->value) == TRUE)
            continue;
        My_Iterator *selectionSetItor = newStackIterator(symbol->selectionSet);
        while (has_itor_next(selectionSetItor))
        {
            Stack *selection = get_itor_next(selectionSetItor);
            My_Iterator *selectionItor = newStackIterator(selection);
            while (has_itor_next(selectionItor))
            {
                SymbolDefine sign = get_itor_next(selectionItor);
                // if (sign > TERMINAL_MAX_RANGE)
                //     sign = sign;
                parseTable[symbol->value - NO_TERMINAL_VALUE_BASE][sign] = productionCount;
            }
            productionCount++;
            my_iterator_free(selectionItor);
        }

        my_iterator_free(selectionSetItor);
    }
    my_iterator_free(itor);
    sdestory(reverSymbolArray, StackDestoryEmpty);
}

void printfParseTable()
{
    printf("\nprintfParsetTable:\n");
    for (int i = 0; i < NO_TERMINAL_MAXRANGE; i++)
    {
        for (int j = 0; j < TERMINAL_MAX_RANGE; j++)
        {
            printf("  %d  ", parseTable[i][j]);
        }
        printf("\n");
    }
}