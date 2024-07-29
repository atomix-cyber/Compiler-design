#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void generateTemp(char *tempName, int *tempCount) {
    sprintf(tempName, "t%d", (*tempCount)++);
}

void printTAC(char *op, char *arg1, char *arg2, char *result) {
    printf("%s = %s %s %s\n", result, arg1, op, arg2);
}

void generateTAC(char *expr) {
    int tempCount = 1;
    char temp[10]; 
    char *p = expr;
    char op;
    char leftOperand[50], rightOperand[50];

    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (isdigit(*p) || (*p == '.' && isdigit(*(p+1)))) {
           
            char num[50];
            int i = 0;
            while (isdigit(*p) || *p == '.') {
                num[i++] = *p++;
            }
            num[i] = '\0';
            strcpy(leftOperand, num);
            while (isspace(*p)) p++;
            op = *p++;
            while (isspace(*p)) p++;
            if (isdigit(*p) || (*p == '.' && isdigit(*(p+1)))) {
                i = 0;
                while (isdigit(*p) || *p == '.') {
                    num[i++] = *p++;
                }
                num[i] = '\0';
                strcpy(rightOperand, num);
            }
            generateTemp(temp, &tempCount);
            printTAC(&op, leftOperand, rightOperand, temp);
            strcpy(leftOperand, temp);
        } else {
            p++;
        }
    }
}

int main() {
    char expr[100];

    printf("Enter a mathematical expression (e.g., 5 + 3 * 2): ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0'; 

    printf("Three-Address Code:\n");
    generateTAC(expr);

    return 0;
}
