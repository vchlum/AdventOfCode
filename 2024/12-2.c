#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* gcc 12-2.c -g -o 12-2 */

typedef struct
{
    long area;
    long corners;
} GardenPlot;


typedef struct
{
    char label;
    GardenPlot *plot;
} Plant;

int plotsSize = 0;
GardenPlot **plots;
Plant **map = NULL;

int corners_get(int x, int y, int mapX, int mapY) {
    int corners = 0;
    char label = map[y][x].label;
    int n = (y > 0) && (map[y-1][x].label == label);
    int e = (x + 1 < mapX) && (map[y][x+1].label == label);
    int s = (y + 1 < mapY) && (map[y+1][x].label == label);
    int w = (x > 0) && (map[y][x-1].label == label);
    int ne = (y > 0) && (x + 1 < mapX) && (map[y-1][x+1].label == label);
    int se = (y + 1 < mapY) && (x + 1 < mapX) && (map[y+1][x+1].label == label);
    int sw = (y + 1 < mapY) && (x > 0) && (map[y+1][x-1].label == label);
    int nw = (y > 0) && (x > 0) && (map[y-1][x-1].label == label);
    if (!n && !e) corners++;
    if (!e && !s) corners++;
    if (!s && !w) corners++;
    if (!w && !n) corners++;
    if (n && e && !ne) corners++;
    if (e && s && !se) corners++;
    if (s && w && !sw) corners++;
    if (w && n && !nw) corners++;
    return corners;
}

GardenPlot *gardenPlot_get(int x, int y, int mapX, int mapY) {
    if (map[y][x].plot != NULL)
        return map[y][x].plot;
    plotsSize++;
    if (plotsSize == 1) {
        plots = calloc(plotsSize, sizeof(GardenPlot *));
    } else {
        plots = realloc(plots, plotsSize * sizeof(GardenPlot *));
    }
    plots[plotsSize - 1] = calloc(1, sizeof(GardenPlot));
    plots[plotsSize - 1]->area = 0;
    plots[plotsSize - 1]->corners = 0;
    return plots[plotsSize - 1];
}

void gardenPlot_set(GardenPlot *plotXY, int x, int y, int mapX, int mapY) {
    if (map[y][x].plot == NULL) {
        map[y][x].plot = plotXY;
        plotXY->area++;
    }
    if (x > 0 && map[y][x - 1].plot == NULL)
        if (map[y][x - 1].label == map[y][x].label) {
            gardenPlot_set(plotXY, x - 1, y, mapX, mapY);
        }
    if (y > 0 && map[y - 1][x].plot == NULL)
        if (map[y - 1][x].label == map[y][x].label) {
            gardenPlot_set(plotXY, x, y - 1, mapX, mapY);
        }
    if (x + 1 < mapX && map[y][x + 1].plot == NULL)
        if (map[y][x + 1].label == map[y][x].label) {
            gardenPlot_set(plotXY, x + 1, y, mapX, mapY);
        }
    if (y + 1 < mapY && map[y + 1][x].plot == NULL)
        if (map[y + 1][x].label == map[y][x].label) {
            gardenPlot_set(plotXY, x, y + 1, mapX, mapY);
        }
}

long long totelPrice() {
    long long res = 0;
    for (int i = 0; i < plotsSize; i++) {
        res += plots[i]->area * plots[i]->corners;
    }
    return res;
}

int main(void) {
    long long res = 0;
    FILE *f = fopen("12.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    int map_line_size = 1;
    map = calloc(map_line_size, sizeof(Plant*));
    int mapX, mapY = -1;
    while ((read = getline(&line, &len, f)) != -1) {
        mapY++;
        if (map_line_size < mapY) {
            map_line_size *= 2;
            map = realloc(map, map_line_size * sizeof(Plant *));
        }
        mapX = strlen(line) -1;
        map[mapY] = calloc(mapX, sizeof(Plant));
        for (int i = 0; i < mapX; i++) {
            map[mapY][i].label = line[i];
            map[mapY][i].plot = NULL;
        }
    }
    mapY++;
    if (line)
        free(line);
    for (int y = 0; y < mapY; y++){
        for (int x = 0; x < mapX; x++) {
            GardenPlot *plotXY = gardenPlot_get(x, y, mapX, mapY);
            gardenPlot_set(plotXY, x, y, mapX, mapY);
        }
    }
    for (int y = 0; y < mapY; y++)
        for (int x = 0; x < mapX; x++)
            map[y][x].plot->corners += corners_get(x, y, mapX, mapY);
    res = totelPrice();
    printf("%lld\n", res);
    fclose(f);
    return 0;
}