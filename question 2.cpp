#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
bool isSingleLineComment(const char *line) {
    return line[0] == '/' && line[1] == '/';
}
bool isMultiLineCommentStart(const char *line) {
    return line[0] == '/' && line[1] == '*';
}
bool isMultiLineCommentEnd(const char *line) {
    return line[0] == '*' && line[1] == '/';
}
void processFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    char line[1024];
    bool inMultiLineComment = false;
    while (fgets(line, sizeof(line), file)) {
        if (isMultiLineCommentStart(line)) {
            inMultiLineComment = true;
        }
        if (inMultiLineComment) {
            if (isMultiLineCommentEnd(line)) {
                inMultiLineComment = false;
                printf("Multi-line comment ended.\n");
                continue;
            }
            printf("Line is part of a multi-line comment.\n");
            continue;
        }
        if (isSingleLineComment(line)) {
            printf("Single-line comment: %s", line);
            continue;
        }
        printf("Line is not a comment: %s", line);
    }
    if (inMultiLineComment) {
        printf("Warning: Multi-line comment not closed.\n");
    }
    fclose(file);
}
int main() {
    const char *filename = "input.c"; 
    processFile(filename);
    return 0;
}
