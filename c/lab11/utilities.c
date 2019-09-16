    //
// Created by Dima on 05.05.2019.
//

#include "utilities.h"

char** get_words(char *source, int *amount){
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
    if(strlen(source) == 0){
        return target;
    }
    target[0] = words;
    (*amount)++;
    stop = strstr(source, ".");
    *stop = 0;
    while(((psep = strstr(words, " ")) != NULL)&&(psep<stop)){
        *psep = 0;
        if(strlen(words)>0){
            words = psep+1;
            target[*amount] = words;
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
    }

    return target;
}

List append(List list, char *value){
    if(list == NULL){
        list = malloc(sizeof(pList));
        if(list == NULL){
            return NULL;
        }
        list->head = NULL;
        list->tail = NULL;
    }
    Node new_node = malloc(sizeof(pNode));

    new_node->value = calloc(strlen(value)+1, sizeof(char));
    new_node->size = strlen(value);
    strcpy(new_node->value, value);

    new_node->next = NULL;
    new_node->prev = list->tail;
    if(list->tail != NULL){
        list->tail->next = new_node;
    }
    list->tail = new_node;
    if(list->head == NULL){
        list->head = list->tail;
    }
    return list;
}

void delete_list(List list){
    if(list != NULL){
        Node node;
        while(list->head != NULL){
            node = list->head;
            if(node == list->tail){
                list->tail = NULL;
            }
            list->head = list->head->next;
            free(node->value);
            free(node);
        }
        free(list);
    }
}

long int max_lenght(List list){
    if(list != NULL){
        long int max_size = 0;
        Node node = list->head;
        while(node != NULL){
            if(node->size > max_size){
                max_size = node->size;
            }
            node = node->next;
        }
        return max_size;
    }
    return -1;
}

void print_sentence(List list){
    if(list != NULL){
        Node node = list->head;
        while(node != NULL){
            fputs(node->value, stdout);
            printf(" ");
            node = node->next;
        }
    }
}

List magick(List list, long int max){
    Node new_node;
    if(list != NULL){
        Node node = list->head;
        while(node != NULL){
            if(node->size == max){
                new_node = malloc(sizeof(pNode));
                new_node->value = calloc(strlen(node->value)+1, sizeof(char));
                new_node->size = strlen(node->value);
                strcpy(new_node->value, node->value);

                new_node->next = node;
                new_node->prev = node->prev;
                if(node->prev != NULL){
                    node->prev->next = new_node;
                }else{
                    list->head = new_node;
                }
                node->prev = new_node;
            }
            node = node->next;
        }
    }
    return list;
}