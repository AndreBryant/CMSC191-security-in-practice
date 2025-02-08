#ifndef AUTH_FUNCTIONS_H
#define AUTH_FUNCTIONS_H

typedef struct {
    char *id, *data;
} Entry;

void get_all_entries(Entry *arr[], int size, int page, const char *table_name) ;
void print_all_entries(Entry *arr[], int size) ;
void free_all_entries(Entry *arr[], int size) ;

void login(Entry *usernames[], Entry *passwords[], char* username, char* password, int *is_logged_in) ;

#endif