#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#define SUCCESS 0;
#define STRUCTURE_ERROR -1;
#define DOMAIN_ERROR -2;
#define NAME_ERROR -3;

int valid_domain_symbols(char* str) {
    size_t i = 1;
    while (str[i]) {
        if ((str[i] < '-') || (str[i] == '/') || (str[i] > '9' && str[i] < 'A')
            || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z') {
            return 0;
        }
        i++;
    }
    return 1;
}

int valid_name_symbols(char* str, size_t size) {
    size_t i = 0;
    while (i < size) {
        if ((str[i] < '-') || (str[i] == '/') || (str[i] > '9' && str[i] < 'A')
            || (str[i] > 'Z' && str[i] < 'a' && str[i] != '_') || str[i] > 'z') {
            return 0;
        }
        i++;
    }
    return 1;
}

char* check_structure(char* address) {
    if (!address) {
        return NULL;
    }

    char* sep = strchr(address, '@');
    if (!sep) {
        return NULL;
    }

    if (sep == address) {
        return NULL;
    }

    if (strchr(sep + 1, '@')) {
        return NULL;
    }
    return sep;
}

char* check_domain(char* sep) {
    if (!sep) {
        return NULL;
    }

    if (!valid_domain_symbols(sep)) {
        return NULL;
    }

    char* point = strchr(sep, '.');
    if (!point) {
        return NULL;
    }

    if (sep + 1 == point) {
        return NULL;
    }

    while (point) {
        if (*(point + 1) == '.' || *(point + 1) == '\0') {
            return NULL;
        }
        point = strchr(point + 1, '.');
    }

    return sep;
}

int valid_first_last(char sym) {
    if ((sym >= 'a' && sym <= 'z') || (sym >= 'A' && sym <= 'Z')
        || (sym >= '0' && sym <= '9')) {
        return 1;
    }

    return 0;
}

char* check_name(char* address, char* sep) {
    if (!address || !sep) {
        return NULL;
    }

    if (!(valid_name_symbols(address, sep - address))) {
        return NULL;
    }

    if (!valid_first_last(*address) || !(valid_first_last(*(sep - 1)))) {
        return NULL;
    }

    return address;
}

int check_email(char* address) {
    char* sep = check_structure(address);
    if (!sep) {
        return STRUCTURE_ERROR;
    }

    if (!check_domain(sep)) {
        return DOMAIN_ERROR;
    }

    if (!check_name(address, sep)) {
        return NAME_ERROR;
    }

    return SUCCESS;
}

char* parse_name(char* address) {
    if (!address) {
        return NULL;
    }
    char* sep = strchr(address, '@');

    char* name = NULL;
    if (asprintf(&name, "%.*s", (int)(sep - address), address) == -1) {
        return NULL;
    }

    return name;
}


char* parse_domain(char* address) {
    if (!address) {
        return NULL;
    }

    char* point = strrchr(address, '.');

    size_t bytes = 0;
    while (point[bytes]) {
        bytes++;
    }

    char* domain = NULL;
    if (asprintf(&domain, "%.*s", (int)bytes, point) == -1) {
        return NULL;
    }
    return domain;
}


char* parse_postname(char* address) {
    if (!address) {
        return NULL;
    }

    char* sep = strchr(address, '@');
    char* point = strrchr(address, '.');

    char* postname = NULL;

    if (asprintf(&postname, "%.*s", (int)(point - (sep + 1)), sep + 1) == -1) {
        return NULL;
    }
    return postname;
}

Email* parse(char* address) {
    if (check_email(address)) {
        return NULL;
    }

    Email* email = calloc(1, sizeof(Email));
    if (!email) {
        return NULL;
    }

    email->name = parse_name(address);
    email->postname = parse_postname(address);
    email->domain = parse_domain(address);

    return email;
}

void free_email(Email* email) {
    if (email->name) {
        free(email->name);
    }
    if (email->postname) {
        free(email->postname);
    }
    if (email->domain) {
        free(email->domain);
    }
    free(email);
}

void print_struct(Email* email) {
    if (!email) {
        return;
    }
    if (email->name) {
        printf("%s\n", (email->name));
    }
    if (email->postname) {
        printf("%s\n", (email->postname));
    }
    if (email->domain) {
        printf("%s\n", (email->domain));
    }
}
