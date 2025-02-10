#include "auth_functions.h"
#include "auth_structs.h"
#include "auth_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login(int *auth_stage, int *user_id) {
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    int username_id = -1;

    Entry *usernames[ARR_SIZE] = {NULL};
    _get_all_entries(usernames, 0, 0,"usernames");

    while(1) {
        printf("Please enter your username: ");
        fgets(username, MAX_INPUT, stdin);
        _remove_newline(username);

        username_id = -1;

        int i = 0;
        while (usernames[i] != NULL) {
            if (!strcmp(usernames[i]->data, username)) {
                username_id = atoi(usernames[i]->id);
                break;
            }
            i++;
        }

        if (username_id != -1) {
            break;
        }

        printf("Username not found. Try Again.\n");
    }

    Entry *passwords[ARR_SIZE] = {NULL};
    _get_all_entries(passwords, 0, 0, "passwords");

    int found = 0;
    while(!found) {

        printf("Please enter your password: ");
        fgets(password, MAX_INPUT, stdin);
        _remove_newline(password);

        int i = 0;
        while(passwords[i] != NULL) {
            if (atoi(passwords[i]->id) == username_id && !strcmp(passwords[i]->data, password)) {
                found = 1;
                (*auth_stage)++; // Next stage
                (*user_id) = username_id;
                printf("Login Successful!\n");
                break;
            }
            i++;
        }

        printf("Incorrect Password. Please try again.\n");
    }

    _free_all_entries(usernames);
    _free_all_entries(passwords);
}

void security_question(int *auth_stage, int *user_index) {
    char answer[MAX_INPUT];

    ComplexEntry *security_questions[ARR_SIZE] = {NULL};
    _get_all_complex_entries(security_questions, 0, 0, "security_questions");

    int found = 0;
    while(!found) {

        printf("To verify further, please answer the following security question:\n");
        printf("%s ", security_questions[*user_index]->data->question);
        fgets(answer, MAX_INPUT, stdin);
        _remove_newline(answer);

        int i = 0;
        while(security_questions[i] != NULL) {
            if (atoi(security_questions[i]->id) == *user_index && !strcmp(security_questions[i]->data->answer, answer)) {
                found = 1;
                (*auth_stage)++; // Next stage
                break;
            }
            i++;
        }
    }
    _free_all_complex_entries(security_questions);
}