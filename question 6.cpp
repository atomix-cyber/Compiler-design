#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_RULES 10
#define MAX_RULE_LENGTH 50
typedef struct {
    char nonTerminal;
    char productions[MAX_RULES][MAX_RULE_LENGTH];
    int numProductions;
} Grammar;
void eliminateLeftRecursion(Grammar *grammar);
void printGrammar(const Grammar *grammar);
void eliminateLeftRecursion(Grammar *grammar) {
    for (int i = 0; i < 1; i++) { 
        Grammar *g = &grammar[i];
        char newNonTerminal = g->nonTerminal + '\''; 
        int j = 0;
        for (int k = 0; k < g->numProductions; k++) {
            if (g->productions[k][0] == g->nonTerminal) {
                char newProduction[MAX_RULE_LENGTH];
                snprintf(newProduction, sizeof(newProduction), "%c%s", newNonTerminal, g->productions[k] + 1);
                strcpy(g->productions[k], newProduction);
            }
        }
        for (int k = 0; k < g->numProductions; k++) {
            if (g->productions[k][0] == g->nonTerminal) {
                char newProduction[MAX_RULE_LENGTH];
                snprintf(newProduction, sizeof(newProduction), "%s%c", g->productions[k] + 1, newNonTerminal);
                strcpy(g->productions[j++], newProduction);
            }
        }
        snprintf(g->productions[j++], sizeof(g->productions[j]), "ε");
        g->numProductions = j;
        Grammar newGrammar;
        newGrammar.nonTerminal = newNonTerminal;
        newGrammar.numProductions = 0;
        for (int k = 0; k < g->numProductions; k++) {
            if (g->productions[k][0] == newNonTerminal) {
                strcpy(newGrammar.productions[newGrammar.numProductions++], g->productions[k] + 1);
            }
        }
        printf("Transformed Grammar for '%c':\n", g->nonTerminal);
        printGrammar(&newGrammar);
    }
}
void printGrammar(const Grammar *grammar) {
    printf("%c → ", grammar->nonTerminal);
    for (int i = 0; i < grammar->numProductions; i++) {
        if (i > 0) printf(" | ");
        printf("%s", grammar->productions[i]);
    }
    printf("\n");
}
int main() {
    Grammar grammar[MAX_RULES];
    int numGrammars = 1; 
    grammar[0].nonTerminal = 'A';
    grammar[0].numProductions = 2;
    strcpy(grammar[0].productions[0], "Aα");
    strcpy(grammar[0].productions[1], "β");
    printf("Original Grammar:\n");
    printGrammar(&grammar[0]);
    eliminateLeftRecursion(grammar);
    return 0;
}
