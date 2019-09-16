#ifndef LAB9_UTILITIES_H
#define LAB9_UTILITIES_H
#define BUFFER_SIZE 200

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    #include <errno.h>
#include "database.h"

char* get_string();
int get_integer();
double get_double();

int select_field(int w_taxes);

void greetings();
int menu();
Person get_person_stdin();
List search();
int real_search();
int delete_record();
int sort_records();
int edit_record();
//Person edit_person(Person person);

#endif //LAB9_UTILITIES_H
