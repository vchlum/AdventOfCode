#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* gcc 15-1.c -g -o 15-1 */

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

void move(char m) {
    int can = 0;
    if (m == '<') {
        if (map[rY][rX - 1] == '#')
            can = 0;
        else if (map[rY][rX - 1] == '.')
            can = 1;
        else if (map[rY][rX - 1] == 'O') {
            int i = rX - 1;
            while (map[rY][i] == 'O')
                i--;
            if (map[rY][i] == '.') {
                can = 1;
                while (i < rX - 1) {
                    map[rY][i] = 'O';
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
        else if (map[rY][rX + 1] == 'O') {
            int i = rX + 1;
            while (map[rY][i] == 'O')
                i++;
            if (map[rY][i] == '.') {
                can = 1;
                while (i > rX + 1) {
                    map[rY][i] = 'O';
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
        else if (map[rY - 1][rX] == 'O') {
            int i = rY - 1;
            while (map[i][rX] == 'O')
                i--;
            if (map[i][rX] == '.') {
                can = 1;
                while (i < rY - 1) {
                    map[i][rX] = 'O';
                    i++;
                }
                map[rY - 1][rX] = '.';
            }
        }
    }
    if (m == 'v') {
        if (map[rY + 1][rX] == '#')
            can = 0;
        else if (map[rY + 1][rX] == '.')
            can = 1;
        else if (map[rY + 1][rX] == 'O') {
            int i = rY + 1;
            while (map[i][rX] == 'O')
                i++;
            if (map[i][rX] == '.') {
                can = 1;
                while (i > rY + 1) {
                    map[i][rX] = 'O';
                    i--;
                }
                map[rY + 1][rX] = '.';
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
            if (map[y][x] == 'O')
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
            mapX = strlen(line);
            mapY += 1;
            map = realloc(map, mapY * sizeof(char *));
            map[mapY - 1] = calloc(mapX, sizeof(char));
            for (int i = 0; i < mapX; i++) {
                if (line[i] == '@') {
                    rX = i;
                    rY = mapY - 1;
                    map[mapY - 1][i] = '.';
                } else
                    map[mapY - 1][i] = line[i];
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

    for (int i = 0; i < numCo; i++) {
        move(coordinates[i]);
    }
    fclose(f);
    printf("%lld\n", getDistanceSum());
    return 0;
}