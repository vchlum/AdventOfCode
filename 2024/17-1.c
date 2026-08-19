#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* gcc 17-1.c -g -o 17-1 -lm */

int A, B, C;

int *prog;
int proglen = 0;
int out[1000];
int outlen = 0;

int getOperand(int operand) {
    switch (operand) {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return A;
        case 5:
            return B;
        case 6:
            return C;
        default:
            return -1;
    }
    return 0;
}

int main(void) {
    FILE *f = fopen("17.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    int p;
    int i;
    while ((read = getline(&line, &len, f)) != -1) {
        if (strlen(line) < 1)
            continue;
        if (strncmp(line, "Register", strlen("Register")) == 0) {
        switch (strcmp(line, "Register ")) {
            case 'A':
                A = atoi(line + strlen("Register ") + 2);
                break;
            case 'B':
                B = atoi(line + strlen("Register ") + 2);
                break;
            case 'C':
                C = atoi(line + strlen("Register ") + 2);
                break;
        }
        }
        if (strncmp(line, "Program:", strlen("Program:")) == 0) {
            char *progline = line + strlen("Program: ");
            prog = malloc(sizeof(int) * 300);
            char *token = strtok(progline, ",");
            while (token != NULL) {
                prog[proglen++] = atoi(token);
                token = strtok(NULL, ",");
            }
        }
    }

    for (i = 0; i < proglen; ) {
        int operand = prog[i + 1];
        int operandCombo = getOperand(operand);
        int newI = 0;
        switch (prog[i]) {
            case 0:
                A = (int) (A / ((int) pow(2, operandCombo)));
                break;
            case 1:
                B = B ^ operand;
                break;
            case 2:
                B = operandCombo % 8;
                break;
            case 3:
                if (A != 0) {
                    i = operand;
                    newI = 1;
                }
                break;
            case 4:
                B = B ^ C;
                break;
            case 5:
                out[outlen++] = operandCombo % 8;
                break;
            case 6:
                B = (int) (A / ((int) pow(2, operandCombo)));
                break;
            case 7:
                C = (int) (A / ((int) pow(2, operandCombo)));
                break;
        }
        if (!newI) {
            i += 2;
        }
    }

    for (int j = 0; j < outlen; j++) {
        printf("%d", out[j]);
        if (j < outlen - 1) {
            printf(",");
        }
    }
    printf("\n");

    fclose(f);
    free(line);
    free(prog);
    return 0;
}