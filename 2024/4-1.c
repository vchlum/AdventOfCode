#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int process_point(char **grid, int i, int j, int num_lines, int len_line) {
    const char * word = "XMAS";
    const int len = strlen(word);
    const int check_len = len - 1;
    int res = 0;

    if (j + check_len < len_line)
        for (int k = 0; k < len; k++) {
            if (grid[i][j + k] != word[k])
                break;
            if (k == len - 1) res ++;
        }
    
    if (j - check_len >= 0)
        for (int k = 0; k < len; k++) {
            if (grid[i][j - k] != word[k])
                break;
            if (k == len - 1) res ++;
        }

    if (i + check_len < num_lines)
        for (int k = 0; k < len; k++) {
            if (grid[i + k][j] != word[k])
                break;
            if (k == len - 1) res ++;
        }
    
    if (i - check_len >= 0)
        for (int k = 0; k < len; k++) {
            if (grid[i - k][j] != word[k])
                break;
            if (k == len - 1) res ++;
        }

    if (j + check_len < len_line && i + check_len < num_lines)
        for (int k = 0; k < len; k++) {
            if (grid[i + k][j + k] != word[k])
                break;
            if (k == len - 1) res ++; 
        }

    if (j - check_len >= 0 && i - check_len >= 0)
        for (int k = 0; k < len; k++) {
            if (grid[i - k][j - k] != word[k])
                break;
            if (k == len - 1) res ++; 
        }

    if (j + check_len < len_line && i - check_len >= 0)
        for (int k = 0; k < len; k++) {
            if (grid[i - k][j + k] != word[k])
                break;
            if (k == len - 1) res ++; 
        }

    if (j - check_len >= 0 && i + check_len < num_lines)
        for (int k = 0; k < len; k++) {
            if (grid[i + k][j - k] != word[k])
                break;
            if (k == len - 1) res ++; 
        }
    return res;
}

int main() {
    FILE *f = fopen("4.input", "r");
    char *line = NULL;
    int num_lines = 0;
    size_t len = 0;
    int len_line = 0;
    int read;
    int res = 0;
    char **grid = NULL;
    int grid_size = 1;

    grid = calloc(grid_size, sizeof(char*));

    while ((read = getline(&line, &len, f)) != -1) {
        num_lines++;
        len_line = strlen(line) - 1;
        if (num_lines > grid_size) {
            grid_size *= 2;
            grid = realloc(grid, grid_size * sizeof(char*));
        }
        grid[num_lines - 1] = (char *)calloc(len_line, sizeof(char));

        int i = 0;
        while (i < len_line) { grid[num_lines - 1][i] = line[i]; i ++;}
    }

    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < len_line; j++) {
            res += process_point(grid, i, j, num_lines, len_line);
        }
    }

    if (line)
        free(line);
    printf("%d\n", res);
    fclose(f);
    return 0;
}
