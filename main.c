#define SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include "auth_functions.h"

int main(int argc, char *argv[]) {

    int page = 3;
    char *passwords[SIZE];
    get_all_passwords(passwords, SIZE, page);

    int i = 0;
    while(1){
        printf("%s\n", passwords[i]);

        if (passwords[i+1] == NULL) {
            break;
        }
        i++;
    }

    free_all_passwords(passwords, SIZE);
    return 0;
}