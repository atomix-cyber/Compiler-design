#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 100
typedef struct Entry {
    char *expression;
    char *result;
    struct Entry *next;
} Entry;
Entry *hashTable[TABLE_SIZE];
unsigned int hash(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TABLE_SIZE;
}
Entry *createEntry(char *expression, char *result) {
    Entry *entry = (Entry *)malloc(sizeof(Entry));
    entry->expression = strdup(expression);
    entry->result = strdup(result);
    entry->next = NULL;
    return entry;
}
void insert(char *expression, char *result) {
    unsigned int index = hash(expression);
    Entry *entry = createEntry(expression, result);
    entry->next = hashTable[index];
    hashTable[index] = entry;
}
char *find(char *expression) {
    unsigned int index = hash(expression);
    Entry *entry = hashTable[index];
    while (entry) {
        if (strcmp(entry->expression, expression) == 0) {
            return entry->result;
        }
        entry = entry->next;
    }
    return NULL;
}
void optimizeExpressions(char **expressions, int count) {
    for (int i = 0; i < count; i++) {
        char *result = find(expressions[i]);
        if (result) {
            printf("%s = %s (common subexpression)\n", expressions[i], result);
        } else {
            printf("%s = %s (new computation)\n", expressions[i], expressions[i]);
            insert(expressions[i], expressions[i]);
        }
    }
}

int main() {
    memset(hashTable, 0, sizeof(hashTable));
    char *expressions[] = {
        "a = b + c",
        "d = b + c",
        "e = a + f",
        "g = b + c",
        "h = a + f"
    };
    int count = sizeof(expressions) / sizeof(expressions[0]);

    printf("Optimized Expressions:\n");
    optimizeExpressions(expressions, count);
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *entry = hashTable[i];
        while (entry) {
            Entry *temp = entry;
            entry = entry->next;
            free(temp->expression);
            free(temp->result);
            free(temp);
        }
    }

    return 0;
}
