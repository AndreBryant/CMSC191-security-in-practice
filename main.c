#define SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include "auth_functions.h"

int main(int argc, char *argv[]) {

    char *passwords[SIZE];
    get_all_passwords(passwords, SIZE);

    for (int i = 0; i < SIZE; i++) {
        printf("%s\n", passwords[i]);
        free(passwords[i]);

        if (passwords[i+1] == NULL) {
            break;
        }
    }
    return 0;
}