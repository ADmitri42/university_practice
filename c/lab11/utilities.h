//
// Created by Dima on 05.05.2019.
//

#ifndef LAB11_UTILITIES_H
#define LAB11_UTILITIES_H

#include <string.h>
#include <malloc.h>
//#include "dstdin.h"

#define STEP_SIZE 100

typedef struct Node{
    char *value;
    long int size;
    struct Node* prev;
    struct Node* next;
} pNode;

typedef pNode* Node;

typedef struct {
    Node head;
    Node tail;
} pList;

typedef pList* List;

char** get_words(char *source, int *amount);
List append(List list, char* value);
void delete_list(List list);
long int max_lenght(List list);
void print_sentence(List list);

List magick(List list, long int max);

#endif //LAB11_UTILITIES_H
