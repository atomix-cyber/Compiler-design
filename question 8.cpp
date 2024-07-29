#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Symbol {
    char name[50];
    char type[50];
    struct Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *table[TABLE_SIZE];
} SymbolTable;
unsigned int hash(char *name) {
    unsigned int hash = 0;
    while (*name) {
        hash = (hash << 5) + *name++;
    }
    return hash % TABLE_SIZE;
}
void initSymbolTable(SymbolTable *symTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        symTable->table[i] = NULL;
    }
}
void insertSymbol(SymbolTable *symTable, char *name, char *type) {
    unsigned int index = hash(name);
    Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
    strcpy(newSymbol->name, name);
    strcpy(newSymbol->type, type);
    newSymbol->next = symTable->table[index];
    symTable->table[index] = newSymbol;
}
Symbol *lookupSymbol(SymbolTable *symTable, char *name) {
    unsigned int index = hash(name);
    Symbol *symbol = symTable->table[index];
    while (symbol) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }
    return NULL;
}
void deleteSymbol(SymbolTable *symTable, char *name) {
    unsigned int index = hash(name);
    Symbol *symbol = symTable->table[index];
    Symbol *prev = NULL;
    
    while (symbol) {
        if (strcmp(symbol->name, name) == 0) {
            if (prev) {
                prev->next = symbol->next;
            } else {
                symTable->table[index] = symbol->next;
            }
            free(symbol);
            return;
        }
        prev = symbol;
        symbol = symbol->next;
    }
}
void displaySymbolTable(SymbolTable *symTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *symbol = symTable->table[i];
        while (symbol) {
            printf("Name: %s, Type: %s\n", symbol->name, symbol->type);
            symbol = symbol->next;
        }
    }
}

int main() {
    SymbolTable symTable;
    initSymbolTable(&symTable);

    insertSymbol(&symTable, "variable1", "int");
    insertSymbol(&symTable, "function1", "void");
    insertSymbol(&symTable, "variable2", "float");

    printf("Symbol Table:\n");
    displaySymbolTable(&symTable);

    printf("\nLookup 'variable1':\n");
    Symbol *symbol = lookupSymbol(&symTable, "variable1");
    if (symbol) {
        printf("Found: Name: %s, Type: %s\n", symbol->name, symbol->type);
    } else {
        printf("Symbol not found.\n");
    }
    printf("\nDeleting 'variable1'.\n");
    deleteSymbol(&symTable, "variable1");
    printf("\nSymbol Table after deletion:\n");
    displaySymbolTable(&symTable);
    return 0;
}
