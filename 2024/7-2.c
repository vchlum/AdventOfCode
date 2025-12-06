#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct eq {
    long long res;
    int *nums;
    int count;
};

long concate(long a, long b) {
    char concate_str[100];
    sprintf(concate_str, "%ld%ld", a, b);
    return atol(concate_str);
}

int main() {
    FILE *f = fopen("7.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    long long res = 0;
    int eq_size = 1;
    struct eq *equations = calloc(eq_size, sizeof(struct eq));
    int eq_num = 0;

    while ((read = getline(&line, &len, f)) != -1) {
        eq_num++;
        if (eq_size < eq_num) {
            eq_size *= 2;
            equations = realloc(equations, eq_size * sizeof(struct eq));
        }
        equations[eq_num - 1].res = atoll(line);
        equations[eq_num - 1].count = 0;
        equations[eq_num - 1].nums = NULL;
        char *ptr = strtok(strchr(line, ':') + 2, " ");
        while(ptr != NULL) {
            equations[eq_num - 1].count++;
            if (equations[eq_num - 1].nums == NULL)
                equations[eq_num - 1].nums = calloc(equations[eq_num - 1].count, sizeof(int));
            else
                equations[eq_num - 1].nums = realloc(equations[eq_num - 1].nums, equations[eq_num - 1].count * sizeof(int));
            equations[eq_num - 1].nums[equations[eq_num - 1].count - 1] = atoi(ptr);
            ptr = strtok(NULL, " ");
        }
    }
    if (line)
        free(line);

    int num_op = 3;
    for (int i = 0; i < eq_num; i++) {
        int num_comb = 1;
        for (int p = 0; p < equations[i].count - 1; p++)
            num_comb = num_comb * num_op;

        for (int c = 0; c < num_comb; c++) {
            long long r = equations[i].nums[0];
            int tmp = c;
            long con;
            for (int p = 0; p < equations[i].count - 1; p++) {
                if (tmp % num_op == 0)
                    r += equations[i].nums[p+1];
                if (tmp % num_op == 1)
                    r *= equations[i].nums[p+1];
                if (tmp % num_op == 2) {
                    if (p == 0)
                        r = concate(equations[i].nums[p], equations[i].nums[p+1]);
                    else
                        r = concate(r, equations[i].nums[p+1]);
                }
                tmp /= num_op;
            }
            if (r == equations[i].res) {
                res += equations[i].res;
                break;
            }
        }
    }

    printf("%lld\n", res);
    fclose(f);
    return 0;
}
