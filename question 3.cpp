#include <stdio.h>
#include <ctype.h>
void recognize_operator(char ch) {
    switch (ch) {
        case '+':
            printf("Recognized operator: +\n");
            break;
        case '-':
            printf("Recognized operator: -\n");
            break;
        case '*':
            printf("Recognized operator: *\n");
            break;
        case '/':
            printf("Recognized operator: /\n");
            break;
        default:
            printf("Not an operator: %c\n", ch);
            break;
    }
}
int main() {
    char input[100];
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            recognize_operator(input[i]);
        }
    }
    return 0;
}
