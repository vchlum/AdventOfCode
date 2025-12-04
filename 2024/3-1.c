#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int process_line(char *line) {
    int res = 0;
    const char *preffix = "mul("; const int preffix_len = strlen(preffix);
    const char *separator = ","; const int separator_len = strlen(separator);
    const char *suffix = ")"; const int suffix_len = strlen(suffix);

    int i = 0;
    while (line[i] != '\n') {
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
