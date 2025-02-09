#ifndef AUTH_FUNCTIONS_H
#define AUTH_FUNCTIONS_H

void login(char* username, char* password, int *auth_stage, int *user_index) ;
void security_question(int *auth_stage, int *user_index) ;

#endif