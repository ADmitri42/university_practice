//
// Created by Dima on 16.03.2019.
//

#include "utilities.h"


List find_or_create_node(List *head, unsigned long int power){
    if (*head == NULL) {
        List new_node = malloc(sizeof(pList));
        new_node->power = power;
        new_node->coefficient = 0;
        new_node->next = NULL;
        *head = new_node;
        return new_node;
    } else if ((*head)->power < power) {
        List new_node = malloc(sizeof(pList));
        new_node->power = power;
        new_node->coefficient = 0;
        new_node->next = *head;
        *head = new_node;
        return new_node;
    }

    List  prev = NULL, term = *head;
    do {
        if (term->power == power) {
            return term;
        } else if (term->power < power) {
            List new_node = malloc(sizeof(pList));
            new_node->power = power;
            new_node->coefficient = 0;
            new_node->next = term;
            if (prev != NULL) {
                prev->next = new_node;
            }
            return new_node;
        }
        prev = term;
        term = term->next;
    } while (term != NULL);
    List new_node = malloc(sizeof(pList));
    new_node->power = power;
    new_node->coefficient = 0;
    new_node->next = NULL;
    prev->next = new_node;
    return new_node;
}

List delete_coeff(List head, long int coefficient){
    if (head == NULL) {
        return NULL;
    }

    List  term2, prev = NULL, term = head;
    while (term != NULL) {
        if (term->coefficient == coefficient) {
            if (prev != NULL) {
                prev->next = term->next;
            } else {
                head = term->next;
            }
            term2 = term->next;
            free(term);
            term = term2;
        } else {
            prev = term;
            term = term->next;
        }
    }
    return head;
}

List delete_power(List head, unsigned long int power){
    if (head == NULL) {
        return NULL;
    }

    List  term2, prev = NULL, term = head;
    while (term != NULL) {
        if (term->power == power) {
            if (prev != NULL) {
                prev->next = term->next;
            } else {
                head = term->next;
                free(term);
            }
            return head;
        } else {
            prev = term;
            term = term->next;
        }
    }
    return head;
}

List add_coeff(List head, unsigned long int power, long int coefficient){
    List node = find_or_create_node(&head, power);
    node->coefficient += coefficient;
    if(node->coefficient == 0){
        head = delete_power(head, power);
    }
    return head;
}

List get_list(){
    List head = NULL;
    long int power, more = 1, coeff;
    while(more){
        system("clear");
        printf("Let's create a polynomial.\n");
        print_list(head);
        printf("Power: ");
        while((get_integer(&power) == 1)||(power < 0)){
            printf("Wrong input. Try again.\n\t");
        }
        printf("Coefficient: ");
        while(get_integer(&coeff) == 1){
            printf("Wrong input. Try again.\n\t");
        }
        head = add_coeff(head, power, coeff);
        print_list(head);
        printf("One more?(1-yes, 0 - no)");
        while((get_integer(&more) == 1)||(0 > more)||( more > 2)){
            printf("Wrong input. Try again.\n\t");
        }
        if(power == 20){
            if(easteregg()){
                printf("Head corruption.\nSORRY:)\n");
                delete_list(head);
                return NULL;
            };
        }
    }
    system("clear");
    printf("Your polynomial:\n\t");
    print_list(head);

    return head;
}

void delete_list(List head){
    List t;
    if (head != NULL) {
        while (head->next != NULL) {
            t = head->next;
            free(head);
            head = t;
        }
    }
}

void print_list(List head){
    if (head != NULL) {
        printf("%ldx%lu", head->coefficient, head->power);
        head = head->next;
        while (head != NULL) {
            if (head->coefficient < 0) {
                printf("%ld", head->coefficient);
            } else {
                printf("+%ld", head->coefficient);
            }
            if (head->power > 0) {
                printf("x%lu", head->power);
            }
            head = head->next;
        }
        printf("\n");
    } else {
        printf("Nothing to show.\n");
    }
}