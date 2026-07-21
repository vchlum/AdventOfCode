#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* gcc 16-1.c -g -o 16-1 */

int sX = -1, sY = -1;
int eX = -1, eY = -1;

enum Face {
    NONE,
    NORTH,
    EAST,
    SOUTH,
    WEST,
};

typedef struct {
    int dist;
    char label;
    int visited;
    int prevX;
    int prevY;
    enum Face face;
} vertex;

vertex **map;
int mapY = 0, mapX = 0;


int setDist(int y1, int x1, int y2, int x2) {
    int price = -1; enum Face face = NONE;

    if (y1 == y2 && x1 > x2 && map[y1][x1].face == NORTH) {price = 1001; face = WEST;}
    if (y1 == y2 && x1 < x2 && map[y1][x1].face == NORTH) {price = 1001; face = EAST;}
    if (y1 > y2 && x1 == x2 && map[y1][x1].face == NORTH) {price = 1; face = NORTH;}
    if (y1 < y2 && x1 == x2 && map[y1][x1].face == NORTH) {price = 2001; face = SOUTH;}

    if (y1 == y2 && x1 > x2 && map[y1][x1].face == EAST) {price = 2001; face = WEST;}
    if (y1 == y2 && x1 < x2 && map[y1][x1].face == EAST) {price = 1; face = EAST;}
    if (y1 > y2 && x1 == x2 && map[y1][x1].face == EAST) {price = 1001; face = NORTH;}
    if (y1 < y2 && x1 == x2 && map[y1][x1].face == EAST) {price = 1001; face = SOUTH;}

    if (y1 == y2 && x1 > x2 && map[y1][x1].face == SOUTH) {price = 1001; face = WEST;}
    if (y1 == y2 && x1 < x2 && map[y1][x1].face == SOUTH) {price = 1001; face = EAST;}
    if (y1 > y2 && x1 == x2 && map[y1][x1].face == SOUTH) {price = 2001; face = NORTH;}
    if (y1 < y2 && x1 == x2 && map[y1][x1].face == SOUTH) {price = 1; face = SOUTH;}

    if (y1 == y2 && x1 > x2 && map[y1][x1].face == WEST) {price = 1; face = WEST;}
    if (y1 == y2 && x1 < x2 && map[y1][x1].face == WEST) {price = 2001; face = EAST;}
    if (y1 > y2 && x1 == x2 && map[y1][x1].face == WEST) {price = 1001; face = NORTH;}
    if (y1 < y2 && x1 == x2 && map[y1][x1].face == WEST) {price = 1001; face = SOUTH;}

    int newDist = map[y1][x1].dist + price;
    if (map[y2][x2].dist > newDist) {
        map[y2][x2].dist = newDist;
        map[y2][x2].face = face;
        map[y2][x2].prevX = x1;
        map[y2][x2].prevY = y1;
    }
    if (map[y2][x2].label == 'E')
        return 1;
    return 0;
}

int main(void) {
    FILE *f = fopen("16.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    int p;
    map = calloc(0, sizeof(vertex *));
    while ((read = getline(&line, &len, f)) != -1) {
        if (strlen(line) < 1)
            continue;
        if (strchr(line, '\n') > 0)
            line[strlen(line) - 1] = '\0';
        mapX = strlen(line);
        mapY += 1;
        map = realloc(map, mapY * sizeof(vertex *));
        map[mapY - 1] = calloc(mapX, sizeof(vertex));
        for (int i = 0; i < mapX; i++) {
            map[mapY - 1][i].label = line[i];
            map[mapY - 1][i].dist = INT_MAX;
            map[mapY - 1][i].prevX = -1;
            map[mapY - 1][i].prevY = -1;
            map[mapY - 1][i].face = NONE;
            if (line[i] == '.') {
                map[mapY - 1][i].visited = 0;
            }
            if (line[i] == 'S') {
                map[mapY - 1][i].dist = 0;
                map[mapY - 1][i].visited = 0;
                map[mapY - 1][i].face = EAST;
            }
            if (line[i] == 'E') {
                map[mapY - 1][i].visited = 0;
            }
            if (line[i] == '#') {
                map[mapY - 1][i].dist = -1;
                map[mapY - 1][i].visited = -1;
            }
        }
    }
    if (line)
        free(line);
    int numPoints = 1;
    while (numPoints > 0) {
        numPoints = 0;
        int min = INT_MAX, minX = -1, minY = -1;
        for (int y = 0; y < mapY; y++)
            for (int x = 0; x < mapX; x++) {
                if (map[y][x].visited == 0) {
                    numPoints ++;
                    if (map[y][x].dist < min) {
                        min = map[y][x].dist;
                        minX = x; minY = y;
                    }
                }
            }
        if (numPoints > 0) {
            map[minY][minX].visited = 1;
            if (map[minY][minX - 1].label == '.' || map[minY][minX - 1].label == 'E')
                if (setDist(minY, minX, minY, minX - 1)) { eX = minX - 1; eY = minY; break; }
            if (map[minY - 1][minX].label == '.' || map[minY - 1][minX].label == 'E')
                if (setDist(minY, minX, minY - 1, minX)) { eX = minX; eY = minY - 1; break; }
            if (map[minY][minX + 1].label == '.' || map[minY][minX + 1].label == 'E')
                if (setDist(minY, minX, minY, minX + 1)) { eX = minX + 1; eY = minY; break; }
            if (map[minY + 1][minX].label == '.' || map[minY + 1][minX].label == 'E')
                if (setDist(minY, minX, minY + 1, minX)) { eX = minX; eY = minY + 1; break; }
        }
    }
    fclose(f);
    printf("%ld\n", map[eY][eX].dist);
    return 0;
}
