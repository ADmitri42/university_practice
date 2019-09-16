//
// Created by Dima on 06.03.2019.
//
#define _CRT_SECURE_NO_WARNINGS
#ifndef LAB8_UTILITIES_H
#define LAB8_UTILITIES_H
#ifndef STDIO_H_
#include <stdio.h>
#endif

#include <string.h>

#define BUFFER_SIZE 200
#define STEP_SIZE 10
extern int errno;

int menu();
double* get_array(int* size);
char** get_strings(int* amount);

void print_array(double* array, int size);
void print_strings(char **strings, int size);

int get_integer();
double get_double();



#endif //LAB8_UTILITIES_H
