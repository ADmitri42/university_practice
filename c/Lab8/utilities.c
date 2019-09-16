//
// Created by Dima on 06.03.2019.
//
#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include "utilities.h"
#include "text.h"
#include "binaries.h"

int menu(){
    printf("Hi! What can I do for you?\n\t1-binary file\n\t2-text file\n");
    int mode;
    while(((mode = get_integer()) < 1)||(mode > 2)){
        printf("Wrong input. Try again.\n");
    }
    return mode;
}

double* get_array(int* size){
    printf("Size of array: ");
    while((*size = get_integer()) < 0){
        printf("Wrong input. Try again.\n");
    }
    double *data = malloc(sizeof(double)* *size);
    for (int i = 0; i < *size; i++){
        data[i] = get_double();
    }
    return data;
}

void print_array(double* array, int size){
    for (int i = 0; i < size; i++){
        printf("%.2lf ", array[i]);
    }
    printf("\n");
}

int get_integer(){
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);
    int mode;
    while((sscanf(buffer, "%d", &mode) == 0)){
        printf("Wrong input. Try again.\n");
        fgets(buffer, BUFFER_SIZE, stdin);
    }
    return mode;
}

double get_double() {
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);
    double mode;
    while ((sscanf(buffer, "%lf", &mode) == 0)) {
        printf("Wrong input. Try again.\n");
        fgets(buffer, BUFFER_SIZE, stdin);
    }
    return mode;
}



char** get_strings(int* amount) {
	int mode;
	printf("From file?(1 - yes, 0 - no) ");
	while (((mode = get_integer()) < 0) || (mode > 1)) {
		printf("Wrong input. Try again.\n");
	}
	char **strings;
	if (mode) {
		char *filename = (char*)malloc(sizeof(char)*BUFFER_SIZE);
		fgets(filename, BUFFER_SIZE, stdin);
		if (filename[strlen(filename) - 1] == '\n') {
			filename[strlen(filename) - 1] = '\0';
		}
		strings = read_file_B(filename, amount);
		free(filename);
	} else {
		strings = read_stdin(amount);
	}
	return strings;
}

void print_strings(char **strings, int size){
    for(int i=0;i < size;i++){
        fputs(strings[i], stdout);
		printf("\n");
    }
}
