//
// Created by Dima on 25.03.2019.
//

#include "dstdin.h"

/*********************
 * Concatenate two strings with respect for a memory
 * https://stackoverflow.com/questions/8465006/how-do-i-concatenate-two-strings-in-c/8465083
 *  s1
 *  s2
 *
 */
char* concat(const char *s1, const char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator
    if(result == NULL){
        perror(strerror(errno));
        return NULL;
    }
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
    return result;
}

char* change_length(char *string, long int new_size){
    string = realloc(string, new_size);
    if(string == NULL){
        perror(strerror(errno));
        return NULL;
    }
    string[new_size-1] = 0;
    return string;
}

char* get_string(){
    char *term, *string, buffer[BUFFER_SIZE];
    string = calloc(1, sizeof(char));
    if(string == NULL){
        perror(strerror(errno));
        return NULL;
    }
    term = string;
    do{
        fgets(buffer, BUFFER_SIZE, stdin);
        string = concat(string, buffer);
        free(term);
        if(string == NULL){
            return NULL;
        }
        term = string;
    }while(buffer[strlen(buffer)-1] != '\n');
    return string;
}


int get_integer(long int *var){
    /******************************
     * Arguments:
     *          long int *var - variable for integer
     * Return:
     *          0 - if everything is OK
     *          1 - if the input has no numbers
     *          2 - if input is not only numbers
     */
    char *buffer = get_string();
    if((sscanf(buffer, "%ld", var) == -1)){
        free(buffer);
        return 1;
    } else if (strlen(buffer) - 1 == (long int)floor(log10(*var))+ 1){
        free(buffer);
        return 2;
    }
    free(buffer);
    return 0;
}

long int get_double(double *var){
    /******************************
     * Arguments:
     *          double *var - variable where save number
     * Return:
     *          0 - if everything is OK
     *          1 - if the input has no numbers
     *          2 - if input is not only numbers
     */
    char *buffer = get_string();
    if((sscanf(buffer, "%lf", var) == 0)){
        free(buffer);
        return 1;
    } else if (strlen(buffer) - 1 != (int)floor(log10(*var))+ 1){
        free(buffer);
        return 2;
    }
    free(buffer);
    return 0;
}
