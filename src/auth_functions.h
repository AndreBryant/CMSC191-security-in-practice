#ifndef AUTH_FUNCTIONS_H
#define AUTH_FUNCTIONS_H
#define MAX_INPUT 128

void login(int *auth_stage, int *user_id) ;
void security_question(int *auth_stage, int *user_index) ;

#endif