#include <stdio.h>
#include <ctype.h>
void lexicalAnalyzer(FILE *file) {
    int ch;
    int charCount = 0, wordCount = 0, lineCount = 0;
    int inWord = 0;

    while ((ch = fgetc(file)) != EOF) {
        charCount++;
        if (ch == '\n') {
            lineCount++;
        }
        if (isspace(ch) || ch == '\n' || ch == '\t') {
            if (inWord) {
                wordCount++;
                inWord = 0;
            }
        } else {
            inWord = 1;
        }
    }
    if (inWord) {
        wordCount++;
    }

    printf("Characters: %d\n", charCount);
    printf("Words: %d\n", wordCount);
    printf("Lines: %d\n", lineCount + 1);
}

int main() {
    FILE *file;
    char filename[100];

    printf("Enter the filename to analyze: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    lexicalAnalyzer(file);

    fclose(file);
    return 0;
}
