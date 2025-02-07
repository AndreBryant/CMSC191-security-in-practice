#include "auth_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_all_passwords(char *arr[], int size) {
    FILE *fp = fopen("./db/passwords.txt", "r");

    if (fp == NULL) {
        perror("Error Fetching text file database");
        return;
    }

    char line[1024];
    int i = 0;

    while (i < size && fgets(line, sizeof(line), fp)) {
        arr[i] = malloc(strlen(line) + 1);
        if (arr[i] != NULL) {
            strcpy(arr[i], line);
        } else {
            printf("Memory allocation failed for password %d\n", i);
        }
        i++;
    }

    fclose(fp);
}
