#include <stdio.h>
#include <string.h>
#include <ctype.h>
int is_noun(char *word) {
    const char *nouns[] = {"dog", "cat", "book", "apple"};
    for (int i = 0; i < 4; i++) {
        if (strcmp(word, nouns[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
int is_pronoun(char *word) {
    const char *pronouns[] = {"he", "she", "it"};
    for (int i = 0; i < 3; i++) {
        if (strcmp(word, pronouns[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
int is_verb(char *word) {
    const char *verbs[] = {"is", "are", "eats", "writes"};
    for (int i = 0; i < 4; i++) {
        if (strcmp(word, verbs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
void tokenize(char *str, char tokens[][20], int *count) {
    char *token = strtok(str, " ");
    *count = 0;
    while (token != NULL) {
        strcpy(tokens[*count], token);
        (*count)++;
        token = strtok(NULL, " ");
    }
}
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
int check_grammar(char *sentence) {
    char tokens[10][20];
    int count;
    
    to_lowercase(sentence);
    tokenize(sentence, tokens, &count);
    
    if (count != 3) {
        return 0;
    }
    
    if (!(is_noun(tokens[0]) || is_pronoun(tokens[0]))) {
        return 0;
    }
    
    if (!is_verb(tokens[1])) {
        return 0;
    }
    
    if (!is_noun(tokens[2])) {
        return 0;
    }
    
    return 1;
}

int main() {
    char sentence1[] = "The dog eats apple";
    char sentence2[] = "He writes book";
    char sentence3[] = "She are cat";
    
    printf("Sentence 1: %s\n", check_grammar(sentence1) ? "Valid" : "Invalid");
    printf("Sentence 2: %s\n", check_grammar(sentence2) ? "Valid" : "Invalid");
    printf("Sentence 3: %s\n", check_grammar(sentence3) ? "Valid" : "Invalid");
    
    return 0;
}
