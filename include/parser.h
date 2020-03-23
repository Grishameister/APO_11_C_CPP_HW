#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_


typedef struct Email {
    char* name;
    char* postname;
    char* domain;
} Email;


int valid_domain_symbols(char* str);
int valid_name_symbols(char* str, size_t size);
int valid_first_last(char sym);


char* check_structure(char* address);
char* check_domain(char* sep);
char* check_name(char* address, char* sep);
int check_email(char* address);

char* parse_name(char* address);
char* parse_postname(char* address);
char* parse_domain(char* address);

Email* parse(char* address);

void free_email(Email* email);
void print_struct(Email* email);

#endif  // INCLUDE_PARSER_H_
