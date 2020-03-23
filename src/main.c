#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

#define READ_ERR -4;
#define PARSE_ERR -5;
#define SUCCESS 0;

int main() {
    char address[255] = "";
    if (scanf("%254s", address) != 1) {
        return READ_ERR;
    }

    Email* email = parse(address);
    if (!email) {
        return PARSE_ERR;
    }

    print_struct(email);

    free_email(email);
    return SUCCESS;
}
