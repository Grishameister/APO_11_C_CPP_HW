#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    const char* path_to_text = argv[1];
    clock_t start_t, end_t, total_t;
    start_t = clock();
    char* max = NULL;
    parse_text(path_to_text, &max);
    end_t = clock();
    total_t = (double)(end_t - start_t);
    printf("Total time taken by CPU: %ld\n", total_t);
    free(max);
    return 0;
}
