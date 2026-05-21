#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* gcc 14-2.c -g -o 14-2 */

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
int SECONDS=1000000;

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

void printEasterEgg() {
    system("clear");
    for (int y=0; y < HEIGHT; y++) {
        for (int x=0; x < WIDTH; x++) {
            int c = 0;
            for (int i=0; i < numRobots; i++)
                if (robots[i]->pX == x && robots[i]->pY == y)
                    c++;
            if (c == 0) printf(" "); else printf("*");
        }
        printf("\n");
    }
}

int main(void) {
    FILE *f = fopen("14.input", "r");
    char *line = NULL;
    size_t len = 0;
    char *ptr;
    int read;
    struct timespec ts = {0, 10 * 1000000L};
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
        for (int i = 0; i < numRobots; i++) {
            move(robots[i]);
        }
        // noticed that ever 103 and 101 is something ... visual confirmation before 6640
        if ((27 == s % 103 || 54 == s % 101) && s < 6640) {
            printEasterEgg();
            printf("%d\n", s + 1);
            nanosleep(&ts, NULL);
        }
    }
    fclose(f);
    return 0;
}

