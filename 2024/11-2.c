#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* gcc 11-2.c -g -o 11-2 -lm */

#define CACHE_SIZE (1 << 20) //cache size 1,048,576

typedef struct {
    long long value;
    int blinks;
    long long res;
    int used;
} CacheEntry;

CacheEntry cache[CACHE_SIZE];

// Fowler–Noll–Vo hash function; https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
long long hash(long long value, int blinks) {
    long long h = value * 1099511628211;
    h ^= (long long)blinks * 2654435761;
    return h & (CACHE_SIZE - 1);
}

int cache_get(long long value, int blinks, long long *res) {
    long long index = hash(value, blinks);
    for (int i = 0; i < CACHE_SIZE; i++) {
        CacheEntry *e = &cache[index];
        if (!e->used) return 0;
        if (e->value == value && e->blinks == blinks) {
            *res = e->res;
            return 1;
        }
        index = (index + 1) & (CACHE_SIZE - 1);
    }
    return 0;
}

void cache_put(long long value, int blinks, long long result) {
    long long index = hash(value, blinks);
    for (int i = 0; i < CACHE_SIZE; i++) {
        CacheEntry *e = &cache[index];
        if (!e->used) {
            e->used = 1;
            e->value = value;
            e->blinks = blinks;
            e->res = result;
            return;
        }
        index = (index + 1) & (CACHE_SIZE - 1);
    }
}

int num_digits(long long n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

long long count_stones(long long value, int blinks) {
    long long cached;
    long long res;
    if (blinks == 0) return 1;
    if (cache_get(value, blinks, &cached))
        return cached;
    if (value == 0) {
        res = count_stones(1, blinks - 1);
    } else {
        int n = num_digits(value);
        if (n % 2 == 0) {
            long long left = value / (long long)pow(10, n / 2);
            long long right = value % (long long)pow(10, n / 2);
            res = count_stones(left, blinks - 1) + count_stones(right, blinks - 1);
        } else {
            res = count_stones(value * 2024, blinks - 1);
        }
    }
    cache_put(value, blinks, res);
    return res;
}

int main(void) {
    long long res = 0;
    FILE *f = fopen("11.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    char *ptr;
    read = getline(&line, &len, f);
    if (read != -1) {
        ptr = strtok(line, " ");
        while (ptr != NULL) {
            if (ptr != NULL) {
                long long value = atoll(ptr);
                res += count_stones(value, 75);
            }
            ptr = strtok(NULL, " ");
        }
    }
    if (line)
        free(line);
    printf("%lld\n", res);
    fclose(f);
    return 0;
}
