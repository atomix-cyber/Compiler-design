#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

const char *input;
char current_char;

void error() {
    printf("Syntax error\n");
    exit(1);
}

void next_char() {
    current_char = *input++;
}

void match(char expected) {
    if (current_char == expected) {
        next_char();
    } else {
        error();
    }
}

void E(); 
void E_prime();
void T();
void T_prime();
void F();
void E() {
    T();
    E_prime();
}
void E_prime() {
    if (current_char == '+') {
        match('+');
        T();
        E_prime();
    } else if (current_char == '\0' || current_char == ')') {
    } else {
        error();
    }
}
void T() {
    F();
    T_prime();
}
void T_prime() {
    if (current_char == '*') {
        match('*');
        F();
        T_prime();
    } else if (current_char == '+' || current_char == '\0' || current_char == ')') {
    } else {
        error();
    }
}
void F() {
    if (current_char == '(') {
        match('(');
        E();
        match(')');
    } else if (isdigit(current_char)) {
        while (isdigit(current_char)) {
            next_char();
        }
    } else {
        error();
    }
}

void parse(const char *str) {
    input = str;
    next_char();
    E();
    if (current_char != '\0') {
        error();
    }
    printf("Valid expression\n");
}

int main() {
    const char *expression1 = "3+(2*5)";
    const char *expression2 = "3+*2";

    printf("Parsing expression: %s\n", expression1);
    parse(expression1);

    printf("Parsing expression: %s\n", expression2);
    parse(expression2);

    return 0;
}
