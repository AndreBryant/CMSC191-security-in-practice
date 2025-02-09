#ifndef AUTH_STRUCTS_H
#define AUTH_STRUCTS_H

#define ENTRIES_PER_PAGE 10
#define ARR_SIZE 100

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

#endif