#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct r {
    int first;
    int second;
};

int check_corrected(int *update, int count, struct r *rules, int rule_num) {
    int corrected = 0;
    int correct = 0;
    while(correct == 0) {
        correct = 1;
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < rule_num; j++) {
                if (update[i] == rules[j].first) {
                    for (int k = 0; k < i; k++) {
                        if (update[k] == rules[j].second) {
                            correct = 0;
                            int tmp = update[k];
                            update[k] = update[i];
                            update[i] = tmp;
                            corrected = 1;
                            break;
                        }
                    }
                }
                if (correct == 0) break;
            }
        }
    }
    return corrected;
}

int main() {
    FILE *f = fopen("5.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    int res = 0;
    int rule_size = 1;
    int rule_num = 0;
    struct r *rules = calloc(rule_size, sizeof(struct r));
    
    int update_size = 1;
    int update_num = 0;
    int **updates = calloc(update_size, sizeof(int*));
    int *updates_count = calloc(update_size, sizeof(int));

    while ((read = getline(&line, &len, f)) != -1) {
        if (strchr(line, '|') != NULL) {
            rule_num++;
            if (rule_size < rule_num) {
                rule_size *= 2;
                rules = realloc(rules, rule_size * sizeof(struct r));
            }
            rules[rule_num - 1].first = atoi(line);
            rules[rule_num - 1].second = atoi(strchr(line, '|') + 1);
        }

        if (strchr(line, ',') != NULL) {
            update_num++;
            if (update_size < update_num) {
                update_size *= 2;
                updates = realloc(updates, update_size * sizeof(int*));
                updates_count = realloc(updates_count, update_size * sizeof(int));
            }
            updates[update_num - 1] = calloc(1, sizeof(int));
            updates_count[update_num - 1] = 0;
            char * ptr = strtok(line, ",");
            while (ptr != NULL) {
                int num = atoi(ptr);
                int count = ++updates_count[update_num - 1];
                updates[update_num - 1] = realloc(updates[update_num - 1], count * sizeof(int));
                updates[update_num - 1][count - 1] = num;
                ptr = strtok(NULL, ",");
            }
        }
    }
    if (line)
        free(line);

    for (int i = 0; i < update_num; i++) {
        int count = updates_count[i];
        if (check_corrected(updates[i], count, rules, rule_num)) {
            res += updates[i][(int)(ceil(count/2))];
        }
    }

    printf("%d\n", res);
    fclose(f);
    return 0;
}
