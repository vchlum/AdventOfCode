#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* gcc 14-1.c -g -o 14-1 */

typedef struct
{
    int pX;
    int pY;
    int vX;
    int vY;
} Robot;

Robot **robots;
int numRobots = 0;

int WIDTH=101;
int HEIGHT=103;
int SECONDS=100;

void move(Robot *r) {
    if (r->pX + r->vX < 0)
        r->pX = WIDTH + (r->pX + r->vX);
    else if (r->pX + r->vX >= WIDTH)
        r->pX = r->pX + r->vX - WIDTH;
    else
        r->pX += r->vX;
    if (r->pY + r->vY < 0)
        r->pY = HEIGHT + (r->pY + r->vY);
    else if (r->pY + r->vY >= HEIGHT)
        r->pY = r->pY + r->vY - HEIGHT;
    else
        r->pY += r->vY;
}

void quadrant(Robot *r, int *tl, int *tr, int *bl, int *br) { 
    if (r->pX < WIDTH / 2 && r->pY < HEIGHT / 2)
        *tl += 1;
    if (r->pX >= (WIDTH / 2) + WIDTH % 2 && r->pY < HEIGHT / 2)
        *tr += 1;
    if (r->pX < WIDTH / 2 && r->pY >= (HEIGHT / 2) + HEIGHT % 2)
        *bl += 1;
    if (r->pX >= (WIDTH / 2) + WIDTH % 2 && r->pY >= (HEIGHT / 2) + HEIGHT % 2)
        *br += 1;
}

int main(void) {
    long long res = 1;
    FILE *f = fopen("14.input", "r");
    char *line = NULL;
    size_t len = 0;
    char *ptr;
    int read;
    robots = calloc(numRobots, sizeof(Robot *));
    while ((read = getline(&line, &len, f)) != -1) {
        if (strlen(line) < 3)
            continue;
        numRobots++;
        robots = realloc(robots, numRobots * sizeof(Robot *));
        robots[numRobots - 1] = calloc(1, sizeof(Robot));
        ptr = strtok(line, "=");
        ptr = strtok(NULL, ",");
        robots[numRobots - 1]->pX = atoi(ptr);
        ptr = strtok(NULL, " ");
        robots[numRobots - 1]->pY = atoi(ptr);

        ptr = strtok(NULL, "=");
        ptr = strtok(NULL, ",");
        robots[numRobots - 1]->vX = atoi(ptr);
        ptr = strtok(NULL, " ");
        robots[numRobots - 1]->vY = atoi(ptr);
    }
    if (line)
        free(line);

    for (int s = 0; s < SECONDS; s++) {
        for (int i = 0; i < numRobots; i++)
            move(robots[i]);
    }
    int tl = 0, tr = 0, bl = 0, br = 0;
    for (int i = 0; i < numRobots; i++)
        quadrant(robots[i], &tl, &tr, &bl, &br);
    res = tl * tr * bl *br;

    printf("%lld\n", res);
    fclose(f);
    return 0;
}

