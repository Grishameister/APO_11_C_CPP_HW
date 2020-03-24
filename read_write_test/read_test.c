#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "utils.h"
#include <string.h>

#define ERR_PARSE -9
#define ERR_TEST -10

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    const char* path_to_text = argv[1];
    FILE* test_file = fopen("../test_file.txt", "r");
    if (!test_file) {
        return ERR_OPEN_FILE;
    }
    int descr = fileno(test_file);
    struct stat st;
    if (fstat(descr, &st) != 0) {
        fclose(test_file);
        return ERR_DSCR;
    }


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

    char* ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, descr, 0);
    if (ptr == MAP_FAILED) {
        fclose(test_file);
        free(max);
        return ERR_MMAP;
    }
    if (strcmp(max, ptr)) {
        printf("%s\n", ptr);
        printf("%s\n", max);
        fclose(test_file);
        free(max);
        munmap(ptr, st.st_size);
        printf("TEST FAILED\n");
        return ERR_TEST;
    }

    munmap(ptr, st.st_size);
    printf("TEST SUCCESS\n");
    free(max);
    fclose(test_file);
    return 0;
}
