//
// Created by Dima on 08.03.2019.
//
#define _CRT_SECURE_NO_WARNINGS
#ifndef LAB8_TEXT_H
#define LAB8_TEXT_H
#ifndef STDIO_H_
#include <stdio.h>
#endif
#include <malloc.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 200
#define STEP_SIZE 10
//extern int errno;

char** get_lines(char *source, int *amount);

int create_file_B(char filename[], char **data, int size);
char** read_file_B(char filename[], int *size);
char** read_stdin(int *size);

char** evaluate_B(char** strings, int size, int *new_size);

#endif //LAB8_TEXT_H
