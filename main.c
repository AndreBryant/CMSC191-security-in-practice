#define ARR_SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include "auth_functions.h"

int main(int argc, char *argv[]) {

    int page = 4;
    char *passwords[ARR_SIZE];
    get_all_passwords(passwords, ARR_SIZE, page);

    int i = 0;
    while (i < ARR_SIZE && passwords[i] != NULL) {
        printf("%s\n", passwords[i]);
        i++;
    }

    free_all_passwords(passwords, ARR_SIZE);
    return 0;
}