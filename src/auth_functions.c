#define ENTRIES_PER_PAGE 10
#define ARR_SIZE 100

#include "auth_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *id, *data;
} Entry;

typedef struct {
    char *question, *answer;
} SecurityQuestion;

typedef struct {
    char *id;
    SecurityQuestion *data;
} ComplexEntry;

void _free_all_entries(Entry *arr[]);
void _free_all_complex_entries(ComplexEntry *arr[]);
void _get_all_entries(Entry *arr[], int page, const int number_of_entries, const char *table_name);
void _get_all_complex_entries(ComplexEntry *arr[], int page, const int number_of_entries, const char *table_name);
int _parse_entry(Entry *entry, char *line);

void login(char *username, char *password, int *auth_stage) {
    Entry *usernames[ARR_SIZE] = {NULL};
    _get_all_entries(usernames, 0, 0,"usernames");

    int username_id = -1;
    int i = 0;
    while (usernames[i] != NULL) {
        if (!strcmp(usernames[i]->data, username)) {
            username_id = atoi(usernames[i]->id);
            break;
        }
        i++;
    }

    if (username_id == -1) {
        printf("Username not found.\n");
        _free_all_entries(usernames);
        return;
    }

    int page = (username_id / ENTRIES_PER_PAGE) + 1;
    Entry *passwords[ARR_SIZE] = {NULL};
    _get_all_entries(passwords, page, 1, "passwords");

    if (!strcmp(passwords[username_id]->data, password)) {
        *auth_stage = 1;
    }

    _free_all_entries(usernames);
    _free_all_entries(passwords);
}

void _get_all_entries(Entry *arr[], int page, const int number_of_entries, const char *table_name) {
    /**
     * If page is <= 0, then fetch all entries.
     * If number_of_entries is > 0, then fetch the first number_of_entries entries on the page.
     */
    _free_all_entries(arr);

    char filename[128];
    snprintf(filename, sizeof(filename), "./db/%s.txt", table_name);
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        perror("Error Fetching text file database:\n\tTry checking the table name or the text file in the db directory.\n\t");
        return;
    }

    char line[1024];
    int entries_read = 0;
    int max_entries = (number_of_entries > 0) ? number_of_entries : ARR_SIZE;
    if (page > 0) {
        // for pagination (skip data until start_entry)
        int start_entry = (page - 1) * ENTRIES_PER_PAGE;
        for (int j = 0; j < start_entry; j++) {
            if (fgets(line, sizeof(line), fp) == NULL) {
                printf("Reached the end of the file before the desired page.\n");
                fclose(fp);
                return;
            }
        }
    }

    // Record the Data here
    while ((page <= 0 || entries_read < ENTRIES_PER_PAGE) && entries_read < max_entries && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';

        arr[entries_read] = malloc(sizeof(Entry));

        if (arr[entries_read] == NULL) {
            printf("Memory allocation failed for entry %d\n", entries_read);
            continue;
        }

        if (!_parse_entry(arr[entries_read], line)) {
            free(arr[entries_read]);
            arr[entries_read] = NULL;
        }

        entries_read++;
    }

    fclose(fp);
}

void _get_all_complex_entries(ComplexEntry *arr[], int page, const int number_of_entries, const char *table_name) {
    /**
     * If page is <= 0, then fetch all entries.
     * If number_of_entries is > 0, then fetch the first number_of_entries entries on the page.
     */
    _free_all_complex_entries(arr);

    char filename[128];
    snprintf(filename, sizeof(filename), "./db/%s.txt", table_name);
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        perror("Error Fetching text file database:\n\tTry checking the table name or the text file in the db directory.\n\t");
        return;
    }

    char line[1024];
    int entries_read = 0;
    int max_entries = (number_of_entries > 0) ? number_of_entries : ARR_SIZE;
    if (page > 0) {
        // for pagination (skip data until start_entry)
        int start_entry = (page - 1) * ENTRIES_PER_PAGE;
        for (int j = 0; j < start_entry; j++) {
            if (fgets(line, sizeof(line), fp) == NULL) {
                printf("Reached the end of the file before the desired page.\n");
                fclose(fp);
                return;
            }
        }
    }

    while ((page <= 0 || entries_read < ENTRIES_PER_PAGE) && entries_read < max_entries && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';

        arr[entries_read] = malloc(sizeof(Entry));

        if (arr[entries_read] == NULL) {
            printf("Memory allocation failed for entry %d\n", entries_read);
            continue;
        }

        if (!_parse_complex_entry(arr[entries_read], line)) {
            free(arr[entries_read]);
            arr[entries_read] = NULL;
        }

        entries_read++;
    }

    fclose(fp);
}

int _parse_entry(Entry *entry, char *line) {
    char *id_part = strtok(line, ";");
    char *data_part = strtok(NULL, ";");

    if (id_part != NULL && data_part != NULL) {
        entry->id = strdup(id_part + 3); // skip "id:"
        entry->data = strdup(data_part + 5); // skip "data:"
        return 1;
    } else {
        printf("Invalid format in line: %s\n", line);
        return 0;
    }
}

int _parse_complex_entry(ComplexEntry *entry, char *line) {
    char *id_part = strtok(line, ";");
    char *data_part = strtok(NULL, ";");

    if (id_part != NULL && data_part != NULL) {
        entry->id = strdup(id_part + 3); // skip "id:"

        entry->data = malloc(sizeof(SecurityQuestion));
        if (!entry->data) {
            printf("Memory allocation failed for SecurityQuestion\n");
            free(entry->id);
            return 0;
        }

        char *data_copy = strdup(data_part + 5); // skip "data:" But this should be parsed further
        if (!data_copy) {
            printf("Memory allocation failed for data_copy\n");
            free(entry->id);
            free(entry->data);
            return 0;
        }


        if (!_parse_security_question(entry->data, data_copy)) {
            free(entry->id);
            free(entry->data);
            free(data_copy);
            return 0;
        }

        free(data_copy);
        return 1;
    } else {
        printf("Invalid format in line: %s\n", line);
        return 0;
    }
}

int _parse_security_question(SecurityQuestion *entry, char *data) {
    char *question_part = strtok(data, "|");
    char *answer_part = strtok(NULL, "|");

    if (question_part != NULL && answer_part != NULL) {
        entry->question = strdup(question_part);
        entry->answer = strdup(answer_part);

        if (!entry->question || !entry->answer) {
            printf("Memory allocation failed for security question/answer\n");
            free(entry->question);
            free(entry->answer);
            return 0;
        }

        return 1;
    } else {
        printf("Invalid format in line: %s\n", data);
        return 0;
    }
}

void _print_all_entries(Entry *arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] != NULL) {
            printf("ID: %s, Data: %s\n", arr[i]->id, arr[i]->data);
        }
    }
}

void _free_all_entries(Entry *arr[]) {
    for (int i = 0; i < ARR_SIZE; i++) {
        if (arr[i] != NULL) {
            free(arr[i]->id);
            free(arr[i]->data);
            free(arr[i]);
        }
    }
}

void _free_all_complex_entries(ComplexEntry *arr[]) {
    for (int i = 0; i < ARR_SIZE; i++) {
        if (arr[i] != NULL) {
            free(arr[i]->id);
            if (arr[i]->data) {
                free(arr[i]->data->question);
                free(arr[i]->data->answer);
                free(arr[i]->data);
            }
            free(arr[i]);
        }
    }
}