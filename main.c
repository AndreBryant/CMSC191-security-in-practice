#define ARR_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include "src/auth_functions.h"

int main(int argc, char *argv[]) {

    int page = 0;
    Entry *passwords[ARR_SIZE] = {NULL};
    Entry *usernames[ARR_SIZE] = {NULL};

    get_all_entries(passwords, ARR_SIZE, page, "passwords");
    get_all_entries(usernames, ARR_SIZE, page, "usernames");

    int i = 0;
    while (i < ARR_SIZE && passwords[i] != NULL) {
        printf("ID: %d Username: %s, Password: %s\n", i, usernames[i]->data, passwords[i]->data);
        i++;
    }

    free_all_entries(passwords, ARR_SIZE);
    return 0;
}