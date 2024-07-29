#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EXPR_SIZE 100
#define MAX_INSTR_SIZE 100
typedef struct {
    char op[10];
    char arg1[10];
    char arg2[10];
    char result[10];
} Instruction;
void generateAssembly(Instruction *instructions, int count) {
    printf("Assembly Code:\n");  
    for (int i = 0; i < count; i++) {
        Instruction instr = instructions[i];
        if (strcmp(instr.op, "+") == 0) {
            printf("MOV R1, %s\n", instr.arg1);
            printf("ADD R1, %s\n", instr.arg2);
            printf("MOV %s, R1\n", instr.result);
        } else if (strcmp(instr.op, "-") == 0) {
            printf("MOV R1, %s\n", instr.arg1);
            printf("SUB R1, %s\n", instr.arg2);
            printf("MOV %s, R1\n", instr.result);
        } else if (strcmp(instr.op, "*") == 0) {
            printf("MOV R1, %s\n", instr.arg1);
            printf("MUL R1, %s\n", instr.arg2);
            printf("MOV %s, R1\n", instr.result);
        } else if (strcmp(instr.op, "/") == 0) {
            printf("MOV R1, %s\n", instr.arg1);
            printf("DIV R1, %s\n", instr.arg2);
            printf("MOV %s, R1\n", instr.result);
        } else {
            printf("Unknown operation: %s\n", instr.op);
        }
    }
}
int main() {
    Instruction instructions[MAX_INSTR_SIZE];
    int count = 0;
    strcpy(instructions[count].op, "+");
    strcpy(instructions[count].arg1, "a");
    strcpy(instructions[count].arg2, "b");
    strcpy(instructions[count].result, "t1");
    count++;

    strcpy(instructions[count].op, "*");
    strcpy(instructions[count].arg1, "t1");
    strcpy(instructions[count].arg2, "c");
    strcpy(instructions[count].result, "t2");
    count++;

    strcpy(instructions[count].op, "-");
    strcpy(instructions[count].arg1, "t2");
    strcpy(instructions[count].arg2, "d");
    strcpy(instructions[count].result, "result");
    count++;
    generateAssembly(instructions, count);

    return 0;
}
