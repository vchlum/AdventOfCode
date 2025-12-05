#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *f = fopen("6.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    int res = 0;
    int x, y;
    char guard;
    char *tmp;
    int map_size = 1;
    int map_lines = 0;
    int line_len = 0;
    char **map = calloc(map_size, sizeof(char*));

    while ((read = getline(&line, &len, f)) != -1) {
        map_lines++;
        line_len = strlen(line);
        if (map_size < map_lines) {
            map_size *= 2;
            map = realloc(map, map_size * sizeof(char*));
        }
        map[map_lines -1] = calloc(line_len, sizeof(char));
        int i = 0;
        while (line[i] != '\n') {map[map_lines -1][i] = line[i]; i++;}

        if ((tmp = strchr(line, '^')) != NULL) {x = tmp - line; y = map_lines -1; guard = '^';}
    }
    if (line)
        free(line);

    int startX = x;
    int startY = y;
    for (int obstY = 0; obstY < map_lines; obstY++)
        for (int obstX = 0; obstX < line_len; obstX++) {
            if (map[obstY][obstX] != '.')
                continue;
            x = startX;
            y = startY;
            guard = '^';
            map[obstY][obstX] = '#';
            int counter = map_lines * line_len;
            while (1) {
                if (guard == '^') {
                    if (y - 1 < 0) break;
                    if (map[y - 1][x] == '#') guard = '>'; else y--;
                } else if (guard == '>') {
                    if (x + 1 >= line_len) break;
                    if (map[y][x + 1] == '#') guard = 'v'; else x++;
                } else if (guard == 'v') {
                    if (y + 1 >= map_lines) break;
                    if (map[y + 1][x] == '#') guard = '<'; else y++;
                } else if (guard == '<') {
                    if (x - 1 < 0) break;
                    if (map[y][x - 1] == '#') guard = '^'; else x--;
                }
                if (--counter < 0) {res ++; break;}
            }
            map[obstY][obstX] = '.';
        }

    printf("%d\n", res);
    fclose(f);
    return 0;
}
