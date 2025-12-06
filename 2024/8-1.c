#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct point {
    char antenna;
    char antinode;
};

int main() {
    FILE *f = fopen("8.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    int res = 0;
    int map_size = 1;
    struct point **map = calloc(map_size, sizeof(struct point*));
    int mapX, mapY = -1;
    while ((read = getline(&line, &len, f)) != -1) {
        mapY++;
        if (map_size < mapY) {
            map_size *= 2;
            map = realloc(map, map_size * sizeof(struct point *));
        }
        mapX = strlen(line) -1;
        map[mapY] = calloc(mapX, sizeof(struct point));
        for (int i = 0; i < mapX; i ++) {
            map[mapY][i].antenna = line[i];
            map[mapY][i].antinode = '.';
        }
    }
    if (line)
        free(line);
    mapY++; /* last line */
    int x,y;
    int distX, distY;
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            if (map[i][j].antenna != '.') {
                for (int k = 0; k < mapY; k++) {
                    for (int l = 0; l < mapX; l++) {
                        if (map[i][j].antenna == map[k][l].antenna) {
                            if (i == k && j == l) continue;
                            distX = j - l;
                            distY = i - k;
                            if (k - distY >= 0 && k - distY < mapY && l - distX >= 0 && l - distX < mapX)
                                map[k - distY][l - distX].antinode = '#';
                            if (i + distY >= 0 && i + distY < mapY && j + distX >= 0 && j + distX < mapX)
                                map[i + distY][j + distX].antinode = '#';
                        }
                    }
                }
            }
        }
    }
    res = 0;
    for (int i = 0; i < mapY; i++)
        for (int j = 0; j < mapX; j++)
            if (map[i][j].antinode == '#')
                res++;
    printf("%lld\n", res);
    fclose(f);
    return 0;
}
