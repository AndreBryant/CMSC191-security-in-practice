#include "auth_functions.h"
#include "auth_structs.h"
#include "auth_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login(char *username, char *password, int *auth_stage, int *user_index) {
    Entry *usernames[ARR_SIZE] = {NULL};
    _get_all_entries(usernames, 0, 0,"usernames");

    int username_index = -1;
    int i = 0;
    while (usernames[i] != NULL) {
        if (!strcmp(usernames[i]->data, username)) {
            username_index = atoi(usernames[i]->id);
            break;
        }
        i++;
    }

    if (username_index == -1) {
        printf("Username not found.\n");
        _free_all_entries(usernames);
        return;
    }

    Entry *passwords[ARR_SIZE] = {NULL};
    _get_all_entries(passwords, 0, 0, "passwords");

    if (!strcmp(passwords[username_index]->data, password) && !strcmp(passwords[username_index]->id, usernames[username_index]->id)) {
        (*auth_stage)++; // Next stage
        (*user_index) = username_index;
    }

    _free_all_entries(usernames);
    _free_all_entries(passwords);
}

void security_question(int *auth_stage, int *user_index) {
    ComplexEntry *security_questions[ARR_SIZE] = {NULL};
    _get_all_complex_entries(security_questions, 0, 0, "security_questions");

    printf("Security Question: %s\n", security_questions[*user_index]->data->question);
    printf("Answer: %s\n", security_questions[*user_index]->data->answer);
    _free_all_complex_entries(security_questions);
}