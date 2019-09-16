//
// Created by Dima on 16.03.2019.
//

#ifndef LAB10_UTILITIES_H
#define LAB10_UTILITIES_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "dstdin.h"
#include "easteregg.h"
#define BUFFER_SIZE 200

typedef struct Node{
    unsigned long int power;
    long int coefficient;
    struct Node *next;
} pList;

typedef pList* List;

List add_coeff(List head, unsigned long int power, long int coefficient);
List delete_coeff(List head, long int coefficient);
List get_list();

void delete_list(List head);

void print_list(List head);


#endif //LAB10_UTILITIES_H
