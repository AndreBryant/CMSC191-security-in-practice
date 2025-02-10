#ifndef AUTH_UTILS_H
#define AUTH_UTILS_H
#include "auth_structs.h"

void _remove_newline(char *str) ;
void _free_all_entries(Entry *arr[]) ;
void _free_all_complex_entries(ComplexEntry *arr[]) ;
int _parse_entry(Entry *entry, char *line) ;
int _parse_complex_entry(ComplexEntry *entry, char *line) ;
int _parse_security_question(SecurityQuestion *entry, char *data) ;
void _get_all_entries(Entry *arr[], int page, const int number_of_entries, const char *table_name) ;
void _get_all_complex_entries(ComplexEntry *arr[], int page, const int number_of_entries, const char *table_name) ;

#endif