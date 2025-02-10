#include <stdio.h>
#include <stdlib.h>
#include "src/auth_functions.h"

int main(int argc, char *argv[]) {

    int authentication_stage = 0;
    int user_id = -1;
    int auth_loop = 1;

    while (auth_loop) {
        switch (authentication_stage) {
            case 0:
                system("clear");
                login(&authentication_stage, &user_id);
                break;

            case 1:
                system("clear");
                security_question(&authentication_stage, &user_id);
                break;

            case 2:
                system("clear");

                char input[1];
                printf("User Logged in Successfully! >.<\n");
                printf("Press any [c] to continue or [b] to exit...\n");
                scanf("%s", input);

                if (input[0] == 'c') {
                    auth_loop = 1;
                } else if (input[0] == 'b') {
                    auth_loop = 0;
                }

                break;

            default:
                break;
        }
    }

    return 0;
}