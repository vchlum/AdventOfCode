#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file {
    long id;
};

int main() {
    FILE *f = fopen("9.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    read = getline(&line, &len, f);
    line[strchr(line, '\n') != NULL ? strlen(line) - 1 : strlen(line)] = '\0';
    int disk_size = strlen(line);
    struct file *files = calloc(disk_size, sizeof(struct file));
    int length = 0;
    int id = 0;
    for (int i = 0; i < strlen(line); i++) {
        while (disk_size < length + line[i] - 48) {
            disk_size *= 2;
            files = realloc(files, disk_size * sizeof(struct file));
        }
        if ((i + 1) % 2 == 1) {
            for (int j = 0; j < (line[i] - 48); j++)
                files[j + length].id = id;
            length += line[i] - 48;
            id ++;
        }
        if ((i + 1) % 2 == 0) {
            for (int j = 0; j < (line[i] - 48); j++)
                files[j + length].id = -1;
            length += line[i] - 48;
        }
    }
    for (int i = length - 1; i >= 0; i--) {
        if (files[i].id == -1) continue;
        int more = 1;
        for (int j = 0; j < i; j++) {
            if (files[j].id == -1) {
                more = 0;
                struct file tmp = files[j];
                files[j] = files[i];
                files[i] = tmp;
            }
        }
        if (more) break;
    }
    long long res = 0;
    for (int i = 0; i < length; i++) {
        if (files[i].id == -1) continue;
        res += i * files[i].id;
    }
    printf("%lld\n", res);
}