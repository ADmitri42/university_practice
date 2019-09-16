//
// Created by Dima on 08.03.2019.
//
#define _CRT_SECURE_NO_WARNINGS
#include "binaries.h"


int create_file_A(char filename[], double *data, int size){
    FILE *f = fopen(filename, "wb");
    if (f == NULL){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
    }
    fwrite(&size, sizeof(int), 1, f);
    fwrite(data, sizeof(double), size, f);
    fclose(f);
    return 0;
}

int read_file_A(char filename[], double **data, int *size){
    FILE *f = fopen(filename, "rb");
    if (f == NULL){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
    }

    fread(size, sizeof(int), 1, f);
    *data = (double *)calloc(*size, sizeof(double));
    fread(*data, sizeof(double), *size, f);
    fclose(f);
    return 0;
}

int evaluate_A(double **data, int *size){
    double term, result = 0;
    int index;
    for(int i=0;i<(*size);i++){
        result += (*data)[i]*(*data)[i];
        if((i == 0)||((*data)[i] < (*data)[index])){
            index = i;
        }
    }
    *data = realloc((*data), sizeof(double)*((*size)+1));
    if(*data == NULL){
        printf("Not enough memory.\n");
        return 1;
    }
    (*size)+=1;
    for(index++; index<(*size);index++) {
        term = (*data)[index];
        (*data)[index] = result;
        result = term;
    }
    return 0;
}