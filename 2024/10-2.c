#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_trails(int **map, int startY, int startX, int mapY, int mapX) {
    struct pos {
        int y;
        int x;
        int max;
    };
    int num_trails = 1;
    struct pos *trails = calloc(num_trails, sizeof(struct pos));
    trails[0].y = startY;
    trails[0].x = startX;
    trails[0].max = 0;
    int res = 0;
    int first = 0;
    int change = 1;
    while (change) {
        change = 0;
        int tmp_num = num_trails;
        int y = -1;
        int x = -1;
        for (int n = 0; n < tmp_num; n++) {
            if (trails[n].max == 9)
                continue;
            first = 1;
            y = trails[n].y;
            x = trails[n].x;
            int max = trails[n].max;
            for (int direction = 0; direction < 4; direction++) {
                int pY, pX;
                if (direction % 4 == 0) {
                    pY = y - 1;
                    pX = x;
                }
                if (direction % 4 == 1) {
                    pY = y;
                    pX = x + 1; 
                }
                if (direction % 4 == 2) {
                    pY = y + 1;
                    pX = x;
                }
                if (direction % 4 == 3) {
                    pY = y;
                    pX = x - 1;
                }
                if (pY < 0 || pX < 0 || pY >= mapY || pX >= mapX)
                    continue;
                if (map[pY][pX] == max + 1) {
                    change = 1;
                    if (first) {
                        trails[n].y = pY;
                        trails[n].x = pX;
                        trails[n].max += 1;
                        first = 0;
                    } else {
                        trails = realloc(trails, (++num_trails) * sizeof(struct pos));
                        trails[num_trails - 1].y = pY;
                        trails[num_trails - 1].x = pX;
                        trails[num_trails - 1].max = map[pY][pX];
                    }
                }
            }
        }
    }
    for (int n = 0; n < num_trails; n++) {
        if (trails[n].max == 9) {
            res ++;
        }
    }
    return res;
}

int main() {
    FILE *f = fopen("10.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    int res = 0;
    int map_size = 1;
    int **map = calloc(map_size, sizeof(int*));
    int mapX, mapY = -1;
    while ((read = getline(&line, &len, f)) != -1) {
        mapY++;
        if (map_size < mapY) {
            map_size *= 2;
            map = realloc(map, map_size * sizeof(int *));
        }
        mapX = strlen(line) -1;
        map[mapY] = calloc(mapX, sizeof(int));
        for (int i = 0; i < mapX; i ++) {
            map[mapY][i] = line[i] - 48;
        }
    }
    if (line)
        free(line);
    mapY++;
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            if (map[i][j] == 0)
                res += get_trails(map, i, j, mapY, mapX);
        }
    }
    printf("%d\n", res);
    fclose(f);
    return 0;
}
