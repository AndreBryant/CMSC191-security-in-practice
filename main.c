#include <stdio.h>
#include <stdlib.h>
#include "src/auth_functions.h"

int main(int argc, char *argv[]) {

    int authentication_stage = 0;
    int user_index = -1;
    int auth_loop = 1;

    while (auth_loop) {
        switch (authentication_stage) {
            case 0:
                system("clear");
                login(&authentication_stage, &user_index);
                break;

                case 1:
                system("clear");
                security_question(&authentication_stage, &user_index);
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