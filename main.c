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

    char *username = "Andre0";
    char *password = "pw0";
    int is_logged_in = 0;

    login(usernames, passwords, username, password, &is_logged_in);

    switch (is_logged_in) {
        case 0:
            printf("Login failed.\n");
            break;

        case 1:
            printf("Login successful!\n");
            break;

        default:
            break;
    }

    free_all_entries(usernames, ARR_SIZE);
    free_all_entries(passwords, ARR_SIZE);
    return 0;
}