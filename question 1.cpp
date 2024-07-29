#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_TOKEN_LENGTH 100
typedef enum {
    IDENTIFIER, CONSTANT, OPERATOR, END
} TokenType;
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;
void skipWhitespaceAndComments(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (isspace(c)) continue;
        if (c == '/') {
            int next = fgetc(fp);
            if (next == '/') while ((c = fgetc(fp)) != EOF && c != '\n');
            else if (next == '*') while ((c = fgetc(fp)) != EOF && (c != '*' || (c = fgetc(fp)) != '/'));
            else { ungetc(next, fp); ungetc(c, fp); break; }
        } else { ungetc(c, fp); break; }
    }
}
Token getNextToken(FILE *fp) {
    Token token = {END, ""};
    skipWhitespaceAndComments(fp);
    int c = fgetc(fp);
    if (c == EOF) return token;
    if (isalpha(c) || c == '_') {
        int i = 0;
        do { token.value[i++] = c; c = fgetc(fp); } while (isalnum(c) || c == '_');
        token.value[i] = '\0'; ungetc(c, fp); token.type = IDENTIFIER;
    } else if (isdigit(c)) {
        int i = 0;
        do { token.value[i++] = c; c = fgetc(fp); } while (isdigit(c));
        token.value[i] = '\0'; ungetc(c, fp); token.type = CONSTANT;
    } else if (strchr("+-*/=<>!&|", c)) {
        int i = 0;
        do { token.value[i++] = c; c = fgetc(fp); } while (strchr("+-*/=<>!&|", c));
        token.value[i] = '\0'; ungetc(c, fp); token.type = OPERATOR;
    }
    return token;
}
int main() {
    FILE *fp = fopen("input.c", "r");
    if (fp == NULL) { printf("Failed to open file.\n"); return 1; }

    Token token;
    while ((token = getNextToken(fp)).type != END) {
        switch (token.type) {
            case IDENTIFIER: printf("Identifier: %s\n", token.value); break;
            case CONSTANT: printf("Constant: %s\n", token.value); break;
            case OPERATOR: printf("Operator: %s\n", token.value); break;
            default: break;
        }
    }
    fclose(fp);
    return 0;
}
