#include <stdio.h>
#include <ctype.h>
int is_valid_identifier(const char *str) {
    if (!isalpha(str[0]) && str[0] != '_') {
    }
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return 0; 
        }
    }
    return 1;
}
int main() {
    char input[100];
    printf("Enter an identifier: ");
    scanf("%99s", input);
    if (is_valid_identifier(input)) {
        printf("'%s' is a valid identifier.\n", input);
    } else {
        printf("'%s' is not a valid identifier.\n", input);
    }
    return 0;
}
