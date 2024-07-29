#include <stdio.h>
#include <ctype.h>
int main() {
    char input[100];
    int whitespace_count = 0;
    int newline_count = 0;
    printf("Enter a string (Press Enter to finish):\n");
    fgets(input, sizeof(input), stdin);
    for (int i = 0; input[i] != '\0'; i++) {
        if (isspace(input[i])) {
            if (input[i] == '\n') {
                newline_count++;
            } else {
                whitespace_count++;
            }
        }
    }
    printf("Number of whitespace characters: %d\n", whitespace_count);
    printf("Number of newline characters: %d\n", newline_count);
    return 0;
}
