#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils.h"

#define ERR_PARSE -9

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    const char* path_to_text = argv[1];
    FILE* test_file = fopen("../test_file.txt", "w");
    if (!test_file) {
        return ERR_OPEN_FILE;
    }
    int fd = fileno(test_file);

    char* max = NULL;
    if (parse_text(path_to_text, &max)) {
        free(max);
        fclose(test_file);
        return ERR_PARSE;
    }

    if (!max) {
        fclose(test_file);
        return ERR_NULL;
    }

    write(fd, max, strlen(max) + 1);
    free(max);
    fclose(test_file);
    return 0;
}
