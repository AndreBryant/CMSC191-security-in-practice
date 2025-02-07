#define ENTRIES_PER_PAGE 10

#include "auth_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_all_passwords(char *arr[], int size, int page) {
    // idk maybe free everything in the array first
    free_all_passwords(arr, size);

    FILE *fp = fopen("./db/passwords.txt", "r");

    if (fp == NULL) {
        perror("Error Fetching text file database");
        return;
    }

    char line[1024];
    int i = 0;
    int skipped_data_count = (page - 1) * ENTRIES_PER_PAGE;

    // Skip the first skipped_data_count lines (for pagination)
    for (int j = 0; j < skipped_data_count; j++) {
        if (fgets(line, sizeof(line), fp) == NULL) {
            printf("Reached the end of the file before the desired page.\n");
            fclose(fp);
            return;
        }
    }

    // Record the Data here
    while (i < size && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';

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

void free_all_passwords(char *arr[], int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
}
