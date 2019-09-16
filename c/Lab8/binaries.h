//
// Created by Dima on 08.03.2019.
//
#define _CRT_SECURE_NO_WARNINGS
#ifndef LAB8_BINARIES_H
#define LAB8_BINARIES_H
#ifndef STDIO_H_
#include <stdio.h>
#endif
#include <malloc.h>
#include <string.h>
#include <errno.h>

//extern int errno;
int create_file_A(char filename[], double *data, int size);
int read_file_A(char filename[], double **data, int *size);
int evaluate_A(double **data, int *size);
#endif //LAB8_BINARIES_H
