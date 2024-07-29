#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTION 100
#define MAX_NON_TERMINAL 10
#define MAX_RULE_LENGTH 50
void eliminateLeftFactoring(char productions[MAX_NON_TERMINAL][MAX_PRODUCTION][MAX_RULE_LENGTH], int numProductions, char nonTerminals[MAX_NON_TERMINAL]);
void printProductions(char productions[MAX_NON_TERMINAL][MAX_PRODUCTION][MAX_RULE_LENGTH], int numProductions, char nonTerminals[MAX_NON_TERMINAL]);
void eliminateLeftFactoring(char productions[MAX_NON_TERMINAL][MAX_PRODUCTION][MAX_RULE_LENGTH], int numProductions, char nonTerminals[MAX_NON_TERMINAL]) {
    for (int i = 0; i < numProductions; i++) {
        int j = 0;
        while (j < MAX_PRODUCTION && strlen(productions[i][j]) > 0) {
            for (int k = j + 1; k < MAX_PRODUCTION && strlen(productions[i][k]) > 0; k++) {
                if (productions[i][j][0] == productions[i][k][0]) {
                    char prefix[MAX_RULE_LENGTH];
                    int l = 0;
                    while (productions[i][j][l] && productions[i][j][l] == productions[i][k][l]) {
                        l++;
                    }
                    prefix[l] = '\0';
                    char newNonTerminal = nonTerminals[numProductions];
                    nonTerminals[numProductions++] = newNonTerminal;
                    for (int m = j; m < MAX_PRODUCTION && strlen(productions[i][m]) > 0; m++) {
                        if (strstr(productions[i][m], prefix) == productions[i][m]) {
                            snprintf(productions[i][m], MAX_RULE_LENGTH, "%c%s", newNonTerminal, productions[i][m] + l);
                        }
                    }
                    snprintf(productions[i][MAX_PRODUCTION - 1], MAX_RULE_LENGTH, "%s", prefix);
                    break;
                }
            }
            j++;
        }
    }
}
void printProductions(char productions[MAX_NON_TERMINAL][MAX_PRODUCTION][MAX_RULE_LENGTH], int numProductions, char nonTerminals[MAX_NON_TERMINAL]) {
    for (int i = 0; i < numProductions; i++) {
        printf("%c → ", nonTerminals[i]);
        for (int j = 0; j < MAX_PRODUCTION && strlen(productions[i][j]) > 0; j++) {
            if (j > 0) printf(" | ");
            printf("%s", productions[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char productions[MAX_NON_TERMINAL][MAX_PRODUCTION][MAX_RULE_LENGTH] = {
        {"Aα", "β", ""}, 
    };

    char nonTerminals[MAX_NON_TERMINAL] = {'A', '\0'};
    int numProductions = 1;

    printf("Original Grammar:\n");
    printProductions(productions, numProductions, nonTerminals);

    eliminateLeftFactoring(productions, numProductions, nonTerminals);

    printf("\nGrammar After Left Factoring:\n");
    printProductions(productions, numProductions, nonTerminals);

    return 0;
}
