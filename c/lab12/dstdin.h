//
// Created by Dima on 25.03.2019.
//

#ifndef LAB10_DSTDIN_H
#define LAB10_DSTDIN_H
#define BUFFER_SIZE 200
#define STEP_SIZE 10
#define TERM "\n"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

char* get_string();
int get_integer(long int* var);
long int get_double(double *var);
char** get_words(char *source, int *amount);

#endif //LAB10_DSTDIN_H
