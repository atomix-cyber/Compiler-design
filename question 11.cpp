#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

double evaluate(char *expr) {
    double result = 0.0;
    char op = '+';
    char *p = expr;
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (*p == '(') {
            
            int depth = 1;
            char *end = ++p;
            while (*end && depth > 0) {
                if (*end == '(') depth++;
                if (*end == ')') depth--;
                end++;
            }
            if (depth != 0) {
                printf("Mismatched parentheses\n");
                exit(EXIT_FAILURE);
            }
            char *sub_expr = malloc(end - p + 1);
            strncpy(sub_expr, p, end - p - 1);
            sub_expr[end - p - 1] = '\0';
            double sub_result = evaluate(sub_expr);
            free(sub_expr);
            p = end;

            if (op == '+') result += sub_result;
            else if (op == '-') result -= sub_result;
            else if (op == '*') result *= sub_result;
            else if (op == '/') result /= sub_result;
        } else if (isdigit(*p) || *p == '.') {
            double num = strtod(p, &p);
            if (op == '+') result += num;
            else if (op == '-') result -= num;
            else if (op == '*') result *= num;
            else if (op == '/') result /= num;
        } else {
            op = *p;
            p++;
        }
    }
    return result;
}

int main() {
    char expr[100];

    printf("Enter a mathematical expression: ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0'; 

    double result = evaluate(expr);
    printf("Result: %f\n", result);

    return 0;
}
