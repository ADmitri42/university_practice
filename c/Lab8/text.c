//
// Created by Dima on 08.03.2019.
//
#define _CRT_SECURE_NO_WARNINGS
#include "text.h"
#include <math.h>

char** get_lines(char *source, int *amount){
    /********************************************************************
    *   char *source  - pointer to string                               *
    *   int *amount - pointer to variable where we save amount of words *
    *********************************************************************
    *   return                                                          *
    *       array of pointers to words                                  *
    *********************************************************************/

    char *words, *psep, *stop, **target;
    int size = STEP_SIZE;

    target = (char**)calloc(sizeof(char*), size);
    if(target==NULL){
        *amount = -1;
        return NULL;
    }

    words = source;

    *amount = 0;

    psep = strtok(source, "\n");
    do{
        if(strlen(psep)>0){
            target[*amount] = psep;
            (*amount)++;
        }
        if(*amount==size){
            size += STEP_SIZE;
            target = realloc(target, sizeof(char*)*size);
            if(target==NULL){
                *amount = -1;
                return NULL;
            }
        }
    }while(((psep = strtok(NULL, "\n")) != NULL));


    return target;
}

int create_file_B(char filename[], char **data, int size){
    FILE *f = fopen(filename, "w");
    if (f == NULL){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
    }
    for (int i = 0; i < size; i++){
        fwrite(data[i], 1, strlen(data[i]), f);
        fwrite("\n", 1, 1, f);
    }
    fclose(f);
    return 0;
}

char** read_file_B(char filename[], int *size){
    FILE *f = fopen(filename, "r");
    if (f == NULL){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return NULL;
    }
    char buffer[BUFFER_SIZE];
    char *string;
    *size = 0;

    int max_size = STEP_SIZE;
    string = calloc(1, sizeof(char));
   while(fgets(buffer, BUFFER_SIZE, f) != NULL){
        strcat(string, buffer);
    }
    fclose(f);
    char **data = get_lines(string, size);

    return data;
}

int get_integer_(){
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);
    int mode;
    while((sscanf(buffer, "%d", &mode) == 0)||(mode < 0)||(mode > 1)){
        printf("Wrong input. Try again.\n");
        fgets(buffer, BUFFER_SIZE, stdin);
    }
    return mode;
}

char** read_stdin(int *size){
    char buffer[BUFFER_SIZE];
    char *string;
    *size = 0;
    int cont = 1, max_size = STEP_SIZE;
    string = calloc(1, sizeof(char));
	string[0] = 0;
    while(cont){
        fgets(buffer, BUFFER_SIZE, stdin);
		//string = realloc(string, strlen(string) + strlen(buffer));
        strcat(string, buffer);
        printf("One more?(1 - yes, 0 - no) ");
        cont = get_integer_();
    }
    char **data = get_lines(string, size);
	create_file_B("ready.txt", data, *size);

    return data;
}

char** evaluate_B(char** strings, int size, int *new_size){
    char *number, **new_lines = calloc(sizeof(char*), size);
    int flag;
    *new_size = 0;
    for(int i=0;i<size;i++){
        flag=0;
        for(int j=0; j<strlen(strings[i]);j++){
            if((strings[i][j] <= '9')&&(strings[i][j] >= '0')){
                if(flag == 0) {
                    new_lines[*new_size] = calloc(strlen(strings[i]), sizeof(char));
                    strcpy(new_lines[*new_size], strings[i]);
                }
                new_lines[*new_size][j] = (char)((int)'0' + (int)'9' - strings[i][j]);
                flag++;
            }
        }
		if (flag > 0) {
			number = calloc((int)((ceil(log10(flag)) + 1)),  sizeof(char));
			sprintf(number, "=%d\n", flag);
			//printf("%s, %s", new_lines[*new_size], number);
			//new_lines[*new_size] = realloc(new_lines[*new_size], sizeof(char)*(strlen(new_lines[*new_size]) + strlen(number)));
			strcat(new_lines[*new_size], number);
//			free(number);
			(*new_size)++;
		}
    }
    return new_lines;
}

void delete_strings(char **data, int size){
    // for(int i = 0; i < size; i++){
    //     free(data[i]);
    // }
    free(data);
}