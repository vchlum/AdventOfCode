#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* gcc 15-2.c -g -o 15-2 */

char **map;
int mapY = 0, mapX = 0;
char *coordinates;
int numCo = 0;
int rX = -1;
int rY = -1;

int isCoordinate(char c) {
    if (c == '<')
        return 1;
    if (c == '>')
        return 1;
    if (c == '^')
        return 1;
    if (c == 'v')
        return 1;
    return 0;
}

int checkUp(int depth, int y, int x) {
    if (map[y][x] == '#')
        return 0;
    else if (map[y][x] == '.')
        return depth + 1;
    else if (map[y][x] == '[') {
        depth++;
        int d1 = checkUp(depth, y - 1, x);
        int d2 = checkUp(depth, y - 1, x + 1);
        if (!d1 || !d2) return 0;
        return d1 > d2 ? d1 : d2;
    } else if (map[y][x] == ']') {
        depth++;
        int d1 = checkUp(depth, y - 1, x - 1);
        int d2 = checkUp(depth, y - 1, x);
        if (!d1 || !d2) return 0;
        return d1 > d2 ? d1 : d2;
    }
    return 0;
}

int checkDown(int depth, int y, int x) {
    if (map[y][x] == '#')
        return 0;
    else if (map[y][x] == '.')
        return depth + 1;
    else if (map[y][x] == '[') {
        depth++;
        int d1 = checkDown(depth, y + 1, x);
        int d2 = checkDown(depth, y + 1, x + 1);
        if (!d1 || !d2) return 0;
        return d1 > d2 ? d1 : d2;
    } else if (map[y][x] == ']') {
        depth++;
        int d1 = checkDown(depth, y + 1, x - 1);
        int d2 = checkDown(depth, y + 1, x);
        if (!d1 || !d2) return 0;
        return d1 > d2 ? d1 : d2;
    }
    return 0;
}

void moveUp(int depth, int y, int x) {
    if (depth == 0) return;
    depth--;
    if (map[y][x] == '[') {
        moveUp(depth, y - 1, x);
        moveUp(depth, y - 1, x + 1);
        map[y][x] = '.';
        map[y][x + 1] = '.';
        map[y - 1][x] = '[';
        map[y - 1][x + 1] = ']';
    } else if (map[y][x] == ']') {
        moveUp(depth, y - 1, x - 1);
        moveUp(depth, y - 1, x);
        map[y][x - 1] = '.';
        map[y][x] = '.';
        map[y - 1][x - 1] = '[';
        map[y - 1][x] = ']';
    }
}

void moveDown(int depth, int y, int x) {
    if (depth == 0) return;
    depth--;
    if (map[y][x] == '[') {
        moveDown(depth, y + 1, x);
        moveDown(depth, y + 1, x + 1);
        map[y][x] = '.';
        map[y][x + 1] = '.';
        map[y + 1][x] = '[';
        map[y + 1][x + 1] = ']';
    } else if (map[y][x] == ']') {
        moveDown(depth, y + 1, x - 1);
        moveDown(depth, y + 1, x);
        map[y][x - 1] = '.';
        map[y][x] = '.';
        map[y + 1][x - 1] = '[';
        map[y + 1][x] = ']';
    }
}

void move(char m) {
    int can = 0;
    if (m == '<') {
        if (map[rY][rX - 1] == '#')
            can = 0;
        else if (map[rY][rX - 1] == '.')
            can = 1;
        else if (map[rY][rX - 1] == '[' || map[rY][rX - 1] == ']') {
            int i = rX - 1;
            while (map[rY][i] == '[' || map[rY][i] == ']')
                i--;
            if (map[rY][i] == '.') {
                can = 1;
                while (i < rX - 1) {
                    map[rY][i] = map[rY][i + 1];
                    i++;
                }
                map[rY][rX - 1] = '.';
            }
        }
    }
    if (m == '>') {
        if (map[rY][rX + 1] == '#')
            can = 0;
        else if (map[rY][rX + 1] == '.')
            can = 1;
        else if (map[rY][rX + 1] == '[' || map[rY][rX + 1] == ']') {
            int i = rX + 1;
            while (map[rY][i] == '[' || map[rY][i] == ']')
                i++;
            if (map[rY][i] == '.') {
                can = 1;
                while (i > rX + 1) {
                    map[rY][i] = map[rY][i - 1];
                    i--;
                }
                map[rY][rX + 1] = '.';
            }
        }
    }
    if (m == '^') {
        if (map[rY - 1][rX] == '#')
            can = 0;
        else if (map[rY - 1][rX] == '.')
            can = 1;
        else if (map[rY - 1][rX] == '[') {
            int d1 = checkUp(0, rY - 1, rX);
            int d2 = checkUp(0, rY - 1, rX + 1);
            int depth;
            if (d1 == d2) depth = d1;
            if (d1 < d2) depth = d1;
            if (d1 > d2) depth = d2;
            if (depth) {
                moveUp(depth, rY - 1, rX);
                moveUp(depth, rY - 1, rX + 1);
                map[rY - 1][rX] = '.';
                map[rY - 1][rX + 1] = '.';
                can = 1;
            }
        } else if (map[rY - 1][rX] == ']') {
            int d1 = checkUp(0, rY - 1, rX - 1);
            int d2 = checkUp(0, rY - 1, rX);
            int depth;
            if (d1 == d2) depth = d1;
            if (d1 < d2) depth = d1;
            if (d1 > d2) depth = d2;
            if (depth) {
                moveUp(depth, rY - 1, rX - 1);
                moveUp(depth, rY - 1, rX);
                map[rY - 1][rX] = '.';
                map[rY - 1][rX - 1] = '.';
                can = 1;
            }
        }
    }
    if (m == 'v') {
        if (map[rY + 1][rX] == '#')
            can = 0;
        else if (map[rY + 1][rX] == '.')
            can = 1;
        else if (map[rY + 1][rX] == '[') {
            int d1 = checkDown(0, rY + 1, rX);
            int d2 = checkDown(0, rY + 1, rX + 1);
            int depth;
            if (d1 == d2) depth = d1;
            if (d1 < d2) depth = d1;
            if (d1 > d2) depth = d2;
            if (depth) {
                moveDown(depth, rY + 1, rX);
                moveDown(depth, rY + 1, rX + 1);
                map[rY + 1][rX] = '.';
                map[rY + 1][rX + 1] = '.';
                can = 1;
            }
        } else if (map[rY + 1][rX] == ']') {
            int d1 = checkDown(0, rY + 1, rX - 1); 
            int d2 = checkDown(0, rY + 1, rX);
            int depth;
            if (d1 == d2) depth = d1;
            if (d1 < d2) depth = d1;
            if (d1 > d2) depth = d2;
            if (depth) {
                moveDown(depth, rY + 1, rX - 1);
                moveDown(depth, rY + 1, rX);
                map[rY + 1][rX] = '.';
                map[rY + 1][rX - 1] = '.';
                can = 1;
            }
        }
    }
    if (can && m == '<')
        rX--;
    if (can && m == '>')
        rX++;
    if (can && m == '^')
        rY--;
    if (can && m == 'v')
        rY++;
}

long getDistanceSum() {
    long res = 0;
    for (int y = 0; y < mapY; y++)
        for (int x = 0; x < mapX; x++)
            if (map[y][x] == '[')
                res += 100 * y + x;
    return res;
}

int main(void) {
    FILE *f = fopen("15.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    int p;
    map = calloc(0, sizeof(char *));
    coordinates = calloc(0, sizeof(char));
    while ((read = getline(&line, &len, f)) != -1) {
        if (strlen(line) < 1)
            continue;
        if (line[0] == '#') {
            if (strchr(line, '\n') > 0)
                line[strlen(line) - 1] = '\0';
            mapX = strlen(line) * 2;
            mapY += 1;
            map = realloc(map, mapY * sizeof(char *));
            map[mapY - 1] = calloc(mapX, sizeof(char));
            int x = 0;
            for (int i = 0; i < strlen(line); i++) {
                if (line[i] == '@') {
                    rX = x; rY = mapY - 1;
                    map[mapY - 1][x++] = '.';
                    map[mapY - 1][x++] = '.';
                }
                if (line[i] == '#') {
                    map[mapY - 1][x++] = '#';
                    map[mapY - 1][x++] = '#';
                }
                if (line[i] == 'O') {
                    map[mapY - 1][x++] = '[';
                    map[mapY - 1][x++] = ']';
                }
                if (line[i] == '.') {
                    map[mapY - 1][x++] = '.';
                    map[mapY - 1][x++] = '.';
                }
            }
        }
        if (isCoordinate(line[0])) {
            int i = 0;
            while(isCoordinate(line[i])) {
                numCo++;
                coordinates = realloc(coordinates, numCo * sizeof(char));
                coordinates[numCo - 1] = line[i];
                i++;
            }
        }
    }
    if (line)
        free(line);
    for (int i = 0; i < numCo; i++)
        move(coordinates[i]);
    fclose(f);
    printf("%lld\n", getDistanceSum());
    return 0;
}