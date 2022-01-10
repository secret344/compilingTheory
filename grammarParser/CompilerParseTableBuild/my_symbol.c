#include "my_symbol.h"

MySymbol *newSymbol(SymbolDefine value, BOOL nullable, Stack *productions)
{
    MySymbol *symbol = my_malloc(sizeof(MySymbol));
    symbol->value = value;
    symbol->isNullable = nullable;
    symbol->productions = productions;
    symbol->firstSet = new_stack();
    symbol->followSet = new_stack();
    symbol->selectionSet = new_stack();
    if (value < 256)
    {
        sIntPush(symbol->firstSet, (int)value);
    }
    return symbol;
}
