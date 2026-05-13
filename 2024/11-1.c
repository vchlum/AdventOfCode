#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* gcc 11-1.c -g -o 11-1 -lm */
long long size = 0;
struct stone *head = NULL;

struct stone {
    long long value;
    struct stone *next;
};

struct stone *create_stone(long long value) {
    struct stone *s;
    s = calloc(1, sizeof(struct stone));
    s->value = value;
    s->next = NULL;
    return s;
}

struct stone *insert_stone(struct stone *prev, struct stone *s) {
    size += 1;
    if (prev == NULL) {
        head = s;
    } else {
        s->next = prev->next;
        prev->next = s;
    }
    return s;
}

int num_digits(long long n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

struct stone *blink(struct stone *s) {
    int n = num_digits(s->value);
    if (s->value == 0) {
        s->value = 1;
    } else if (n % 2 == 1) {
        s->value *= 2024;
    } else {
        long long left = s->value / (long long)pow(10, n / 2);
        long long right = s->value % (long long)pow(10, n / 2);
        s->value = left;
        s = insert_stone(s, create_stone(right));
    }
    return s;
}

int main() {
    FILE *f = fopen("11.input", "r");
    char *line = NULL;
    size_t len = 0;
    int read;
    long long res = 0;
    char *ptr;
    struct stone *curr = NULL;

    read = getline(&line, &len, f);
    if (read != -1) {
        ptr = strtok(line, " ");
        while (ptr != NULL) {
            if (ptr != NULL) {
                long long value = atoll(ptr);
                curr = insert_stone(curr, create_stone(value));
            }
            ptr = strtok(NULL, " ");
        }
    }

    int blinks = 0;

    while (blinks < 25) {
        curr = head;
        while (curr != NULL) {
            curr = blink(curr);
            curr = curr->next;
        }
        blinks++;
    }

    if (line)
        free(line);
    res = size;
    printf("%lld\n", res);
    fclose(f);
    return 0;
}
