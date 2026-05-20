#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* gcc 13-2.c -g -o 13-2 -lm */

typedef struct
{
    int aX;
    int aY;
    int bX;
    int bY;
    long long pX;
    long long pY;
} Machine;

int machinesSize = 0;
Machine ** machines;

long long get_cheapest(int idx) {
    double A = 0;
    double B = 0;
    int pX = 0;
    int pY = 0;
    Machine *m = machines[idx]; 
    // aX*A + bX*B = pX
    // aY*A + bY*B = pY
    int det = m->aX * m->bY - m->bX * m->aY;
    if (det == 0) {
        return 0;
    }
    A = (double)(m->pX * m->bY - m->bX * m->pY) / det;
    B = (double)(m->aX * m->pY - m->pX * m->aY) / det;

    if (A < 0 || B < 0)
        return 0;
    if (A != floor(A) || B != floor(B))
        return 0;

    return A * 3 + B * 1;
}

int main(void) {
    long long res = 0;
    FILE *f = fopen("13.input", "r");
    char *line = NULL;
    size_t len = 0;
    char *ptr;
    int read;
    machines = calloc(machinesSize, sizeof(Machine *));
    while ((read = getline(&line, &len, f)) != -1) {
        if (strlen(line) < 3)
            continue;
        if (line[7] == 'A') {
            machinesSize++;
            machines = realloc(machines, machinesSize * sizeof(Machine *));
            machines[machinesSize - 1] = calloc(1, sizeof(Machine));
            ptr = strtok(line, "+");
            ptr = strtok(NULL, ",");
            machines[machinesSize - 1]->aX = atoi(ptr);
            ptr = strtok(NULL, "+");
            ptr = strtok(NULL, "\n");
            machines[machinesSize - 1]->aY = atoi(ptr);
        }
        if (line[7] == 'B') {
            ptr = strtok(line, "+");
            ptr = strtok(NULL, ",");
            machines[machinesSize - 1]->bX = atoi(ptr);
            ptr = strtok(NULL, "+");
            ptr = strtok(NULL, "\n");
            machines[machinesSize - 1]->bY = atoi(ptr);
        }
        if (line[7] == 'X') {
            ptr = strtok(line, "=");
            ptr = strtok(NULL, ",");
            machines[machinesSize - 1]->pX = atoi(ptr) + 10000000000000;
            ptr = strtok(NULL, "=");
            ptr = strtok(NULL, "\n");
            machines[machinesSize - 1]->pY = atoi(ptr) + 10000000000000;
        }
    }
    if (line)
        free(line);
    for (int i = 0; i < machinesSize; i++)
        res += get_cheapest(i);;
    printf("%lld\n", res);
    fclose(f);
    return 0;
}
