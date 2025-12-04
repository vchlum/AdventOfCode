#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a1, const void* b1) {
    int a = *((int*)a1);
    int b = *((int*)b1);
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

int main() {
    int first, second, size;
    int *first_arr = calloc(1, sizeof(int));
    int *second_arr = calloc(1, sizeof(int));
    int array_size = 1;
    
    FILE *f = fopen("1.input", "r");

    size = 0;
    while (fscanf(f, "%d   %d", &first, &second) == 2) {
        size ++;
        if (size > array_size) {
            array_size *= 2;
            first_arr = realloc(first_arr, array_size * sizeof(int));
            second_arr = realloc(second_arr, array_size * sizeof(int));
           
        }
        first_arr[size -1 ] = first;
        second_arr[size -1] = second;
    }
        
    fclose(f);

    qsort(first_arr, size, sizeof(int), compare);
    qsort(second_arr, size, sizeof(int), compare);

    int res = 0;
    for (int i = 0; i < size; i++) {
        res += abs(first_arr[i] - second_arr[i]);
    }
    printf("%d\n", res);

    return 0;
}