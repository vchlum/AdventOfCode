#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* gcc 16-2.c -g -o 16-2 */

int sX = -1, sY = -1;
int eX = -1, eY = -1;

enum Face {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
};

static const int faceDY[4] = {-1, 0, 1, 0};
static const int faceDX[4] = {0, 1, 0, -1};

typedef struct {
    int dist[4];
    char label;
    int visited[4];
    int prevX[4];
    int prevY[4];
    int prevFace[4];
    int onPath;
} vertex;

vertex **map;
int mapY = 0, mapX = 0;

int setDist(int y1, int x1, int f1, int y2, int x2) {
    int moveDir = -1;
    for (int d = 0; d < 4; d++)
        if (y1 + faceDY[d] == y2 && x1 + faceDX[d] == x2)
            moveDir = d;

    int diff = (moveDir - f1 + 4) % 4;
    int turns = (diff == 0) ? 0 : (diff == 2) ? 2 : 1;
    int price = 1 + 1000 * turns;
    int f2 = moveDir;

    int newDist = map[y1][x1].dist[f1] + price;
    if (map[y2][x2].dist[f2] > newDist) {
        map[y2][x2].dist[f2] = newDist;
        map[y2][x2].prevX[f2] = x1;
        map[y2][x2].prevY[f2] = y1;
        map[y2][x2].prevFace[f2] = f1;
    }
    if (map[y2][x2].label == 'E')
        return 1;
    return 0;
}

typedef struct { int y, x, f; } State;

void pushState(State **stack, int *stackSize, int *stackCap, int sy, int sx, int sf) {
    if (*stackSize == *stackCap) {
        *stackCap = *stackCap ? *stackCap * 2 : 64;
        *stack = realloc(*stack, *stackCap * sizeof(State));
    }
    (*stack)[(*stackSize)++] = (State){sy, sx, sf};
}

int getNumChepestPath(int eY, int eX) {
    int minDist = INT_MAX;
    for (int f = 0; f < 4; f++)
        if (map[eY][eX].dist[f] >= 0 && map[eY][eX].dist[f] < minDist)
            minDist = map[eY][eX].dist[f];

    State *stack = NULL;
    int stackSize = 0, stackCap = 0;
    char *stateDone = calloc((size_t)mapY * mapX * 4, sizeof(char));

    for (int f = 0; f < 4; f++)
        if (map[eY][eX].dist[f] == minDist)
            pushState(&stack, &stackSize, &stackCap, eY, eX, f);

    while (stackSize > 0) {
        State cur = stack[--stackSize];
        int idx = (cur.y * mapX + cur.x) * 4 + cur.f;
        if (stateDone[idx])
            continue;
        stateDone[idx] = 1;
        map[cur.y][cur.x].onPath = 1;

        if (map[cur.y][cur.x].label == 'S')
            continue;

        int here = map[cur.y][cur.x].dist[cur.f];
        int py = cur.y - faceDY[cur.f], px = cur.x - faceDX[cur.f];
        for (int pf = 0; pf < 4; pf++) {
            if (map[py][px].dist[pf] < 0)
                continue;
            int diff = (cur.f - pf + 4) % 4;
            int turns = (diff == 0) ? 0 : (diff == 2) ? 2 : 1;
            int price = 1 + 1000 * turns;
            if (map[py][px].dist[pf] + price == here)
                pushState(&stack, &stackSize, &stackCap, py, px, pf);
        }
    }

    free(stack);
    free(stateDone);

    int count = 0;
    for (int y = 0; y < mapY; y++)
        for (int x = 0; x < mapX; x++)
            if (map[y][x].onPath)
                count++;
    return count;
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
            map[mapY - 1][i].onPath = 0;
            for (int f = 0; f < 4; f++) {
                map[mapY - 1][i].dist[f] = INT_MAX;
                map[mapY - 1][i].prevX[f] = -1;
                map[mapY - 1][i].prevY[f] = -1;
                map[mapY - 1][i].prevFace[f] = -1;
                map[mapY - 1][i].visited[f] = 0;
            }
            if (line[i] == 'S') {
                map[mapY - 1][i].dist[EAST] = 0;
            }
            if (line[i] == '#') {
                for (int f = 0; f < 4; f++) {
                    map[mapY - 1][i].dist[f] = -1;
                    map[mapY - 1][i].visited[f] = -1;
                }
            }
        }
    }
    if (line)
        free(line);
    int numPoints = 1;
    while (numPoints > 0) {
        numPoints = 0;
        int min = INT_MAX, minX = -1, minY = -1, minF = -1;
        for (int y = 0; y < mapY; y++)
            for (int x = 0; x < mapX; x++)
                for (int fc = 0; fc < 4; fc++) {
                    if (map[y][x].visited[fc] == 0) {
                        numPoints++;
                        if (map[y][x].dist[fc] < min) {
                            min = map[y][x].dist[fc];
                            minX = x; minY = y; minF = fc;
                        }
                    }
                }
        if (numPoints > 0) {
            map[minY][minX].visited[minF] = 1;
            if (map[minY][minX - 1].label == '.' || map[minY][minX - 1].label == 'E')
                if (setDist(minY, minX, minF, minY, minX - 1)) { eX = minX - 1; eY = minY; break; }
            if (map[minY - 1][minX].label == '.' || map[minY - 1][minX].label == 'E')
                if (setDist(minY, minX, minF, minY - 1, minX)) { eX = minX; eY = minY - 1; break; }
            if (map[minY][minX + 1].label == '.' || map[minY][minX + 1].label == 'E')
                if (setDist(minY, minX, minF, minY, minX + 1)) { eX = minX + 1; eY = minY; break; }
            if (map[minY + 1][minX].label == '.' || map[minY + 1][minX].label == 'E')
                if (setDist(minY, minX, minF, minY + 1, minX)) { eX = minX; eY = minY + 1; break; }
        }
    }

    int count = getNumChepestPath(eY, eX);

    fclose(f);
    printf("%d\n", count);
    return 0;
}
