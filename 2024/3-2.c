#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int enabled = 1;

int process_line(char *line) {
    int res = 0;
    const char *preffix = "mul("; const int preffix_len = strlen(preffix);
    const char *separator = ","; const int separator_len = strlen(separator);
    const char *suffix = ")"; const int suffix_len = strlen(suffix);

    const char *enable = "do()"; const int  enable_len = strlen(enable);
    const char *disable = "don't()"; const int disable_len = strlen(disable);

    int i = 0;
    while (line[i] != '\n') {
        if (strncmp(enable, line + i, enable_len) == 0) enabled = 1;
        if (strncmp(disable, line + i, disable_len) == 0) enabled = 0;

        if (strncmp(preffix, line + i, preffix_len) == 0) {
            char *pos = line + i + preffix_len;
            char *start = pos;

            if (isspace(pos[0])) { i++; continue; }
            int first = atoi(pos);
            if (first == 0 || abs(first) > 999) { i++; continue; }
            while (isdigit(pos[0])) pos++;

            if (pos++[0] != separator[0]) { i++; continue; }

            if (isspace(pos[0])) { i++; continue;}
            int second = atoi(pos);
            if (second == 0 || abs(second) > 999) { i++; continue; }
            while (isdigit(pos[0])) pos++;

            if (pos[0] != suffix[0]) { i++; continue; }

            if (enabled)
                res += first * second;
            i += pos - start;
            continue;
        }
        i++;
    }
    return res;
}

int main() {
    FILE *f = fopen("3.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    int res = 0;

    while ((read = getline(&line, &len, f)) != -1) {
        res += process_line(line);
    }
    if (line)
        free(line);
    printf("%d\n", res);
    fclose(f);
    return 0;
}
