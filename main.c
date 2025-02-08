#include <stdio.h>
#include <stdlib.h>
#include "src/auth_functions.h"

int main(int argc, char *argv[]) {

    // system("clear");
    char *username = "Andre0";
    char *password = "pw0";
    int authentication_stage = 0;
    int auth_loop = 1;

    while (auth_loop) {
        switch (authentication_stage) {
            case 0:
                printf("User not logged in.\n");
                printf("Press any key to continue...\n");
                getchar();
                login(username, password, &authentication_stage);
                break;

            case 1:
                printf("Password matches with username! Now checking security questions\n");
                printf("Press any key to continue...\n");
                getchar();
                auth_loop = 0;
                // char *answer = "1827366485";
                // security_question(username, password, answer,&authentication_stage);
                break;

            case 2:
                printf("User Logged in Successfully! >.<\n");
                printf("Press any key to continue...\n");
                getchar();
                auth_loop = 0;
                break;

            default:
                break;
        }
    }

    return 0;
}