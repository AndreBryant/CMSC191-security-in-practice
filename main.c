#include <stdio.h>
#include <stdlib.h>
#include "src/auth_functions.h"

int main(int argc, char *argv[]) {

    // system("clear");
    char *username = "Andre3";
    char *password = "pw3";
    char *answer = "1827366485";

    int authentication_stage = 0;
    int user_index = -1;
    int auth_loop = 1;

    while (auth_loop) {
        switch (authentication_stage) {
            case 0:
                printf("User not logged in.\n");
                printf("Press any key to continue...\n");
                getchar();
                login(username, password, &authentication_stage, &user_index);
                break;

            case 1:
                printf("Password matches with username! Now checking security questions\n");
                printf("Press any key to continue...\n");
                getchar();
                security_question(&authentication_stage, &user_index);
                auth_loop = 0;
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