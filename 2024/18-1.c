#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* gcc 18-1.c -g -o 18-1 */

#define MEM_SIZE 71
#define NUM_BYTES 1024

int **input = NULL;
int input_size = 0;
char mem[MEM_SIZE][MEM_SIZE] = {0};
int visited[MEM_SIZE][MEM_SIZE] = {0};
int distance[MEM_SIZE][MEM_SIZE] = {0};
int s[2] = {0,0};

int get_min(int *min_x, int *min_y) {
    int min_dist = INT_MAX;
    *min_x = -1;
    *min_y = -1;
    for (int y = 0; y < MEM_SIZE; y++) {
        for (int x = 0; x < MEM_SIZE; x++) {
            if (distance[y][x] == -1) continue;
            if (visited[y][x]) continue;
            if (distance[y][x] < min_dist) {
                min_dist = distance[y][x];
                *min_x = x;
                *min_y = y;
            }
        }
    }
    return (*min_x != -1 && *min_y != -1);
}

void *set_neighbors(int x, int y) {
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (nx >= 0 && nx < MEM_SIZE && ny >= 0 && ny < MEM_SIZE) {
            if (distance[ny][nx] != -1 && !visited[ny][nx]) {
                int new_dist = distance[y][x] + 1;
                if (new_dist < distance[ny][nx]) {
                    distance[ny][nx] = new_dist;
                }
            }
        }
    }
}

int main(void) {
    FILE *f = fopen("18.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    int p;
    int i;
    int x, y;
    while ((read = getline(&line, &len, f)) != -1) {
        if (strlen(line) < 1)
            continue;

        char *token = strtok(line, ",");
        x = atoi(token);
        token = strtok(NULL, ",");
        y = atoi(token);
        input_size ++;
        if (input == NULL) {
            input = malloc(sizeof(int *) * input_size);
        } else {
            input = realloc(input, sizeof(int *) * input_size);
        }
        input[input_size - 1] = malloc(sizeof(int) * 2);
        input[input_size - 1][0] = x;
        input[input_size - 1][1] = y;
    }

    for (y = 0; y < MEM_SIZE; y++) {
        for (x = 0; x < MEM_SIZE; x++) {
            distance[y][x] = INT_MAX;
        }
    }
    for (i = 0; i < NUM_BYTES; i++) {
        x = input[i][0];
        y = input[i][1];
        if (x >= 0 && x < MEM_SIZE && y >= 0 && y < MEM_SIZE) {
            mem[y][x] = '#';
            distance[y][x] = -1;
            visited[y][x] = 1;
        }
    }
    distance[s[1]][s[0]] = 0;
    visited[s[1]][s[0]] = 1;
    set_neighbors(s[0], s[1]);
    int min_x, min_y;
    while (get_min(&min_x, &min_y)) {
        visited[min_y][min_x] = 1;
        set_neighbors(min_x, min_y);
    }
    printf("%d\n", distance[MEM_SIZE - 1][MEM_SIZE - 1]);
    fclose(f);
    free(line);
    return 0;
}