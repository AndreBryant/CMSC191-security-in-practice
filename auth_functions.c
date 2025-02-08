#define ENTRIES_PER_PAGE 2

#include "auth_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_password(Entry *entry, char *line);
int parse_username(Entry *entry, char *line);

void get_all_entries(Entry *arr[], int size, int page, const char *table_name) {
    // idk maybe free everything in the array first
    free_all_entries(arr, size);

    char filename[256];
    snprintf(filename, sizeof(filename), "./db/%s.txt", table_name);
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        perror("Error Fetching text file database:\n\tTry checking the table name or the text file in the db directory.\n\t");
        return;
    }

    char line[1024];
    int entries_read = 0;
    if (page > 0) {
        int start_entry = (page - 1) * ENTRIES_PER_PAGE;
        // for pagination (skip data until start_entry)
        for (int j = 0; j < start_entry; j++) {
            if (fgets(line, sizeof(line), fp) == NULL) {
                printf("Reached the end of the file before the desired page.\n");
                fclose(fp);
                return;
            }
        }
    }

    // Record the Data here
    while ((page <= 0 || entries_read < ENTRIES_PER_PAGE) && entries_read < size && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';

        arr[entries_read] = malloc(sizeof(Entry));
        if (arr[entries_read] == NULL) {
            printf("Memory allocation failed for password %d\n", entries_read);
            continue;
        }

        if (arr[entries_read] == NULL) {
            printf("Memory allocation failed for entry %d\n", entries_read);
            continue;
        }

        if (!strcmp(table_name, "passwords")) {
            if (!parse_password(arr[entries_read], line)) {
                free(arr[entries_read]);
                arr[entries_read] = NULL;
            }
        } else if (!strcmp(table_name, "usernames")) {
            if (!parse_username(arr[entries_read], line)) {
                free(arr[entries_read]);
                arr[entries_read] = NULL;
            }
        }

        entries_read++;
    }

    fclose(fp);
}

void free_all_entries(Entry *arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] != NULL) {
            free(arr[i]->id);
            free(arr[i]->data);
            free(arr[i]);
        }
    }
}

int parse_password(Entry *entry, char *line) {
    char *id_part = strtok(line, ";");
    // i didnt know until now
    // strtok(NULL, dlm) should continue from the last string passed to it
    char *pw_part = strtok(NULL, ";");

    if (id_part != NULL && pw_part != NULL) {
        entry->id = strdup(id_part + 3); // skip "id:"
        entry->data = strdup(pw_part + 3); // skip "pw:"
        return 1;
    } else {
        printf("Invalid format in line: %s\n", line);
        return 0;
    }
}

int parse_username(Entry *entry, char *line) {
    char *id_part = strtok(line, ";");
    char *data_part = strtok(NULL, ";");

    if (id_part != NULL && data_part != NULL) {
        entry->id = strdup(id_part + 3); // skip "id:"
        entry->data = strdup(data_part + 5); // skip "user:"
        return 1;
    } else {
        printf("Invalid format in line: %s\n", line);
        return 0;
    }
}