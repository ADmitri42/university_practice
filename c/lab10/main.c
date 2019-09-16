#include <stdio.h>
#include "utilities.h"
//#include "dstdin.c"

long int main() {
    long int c;
    List list = get_list();
    if(list == NULL){
        return 1;
    }
    printf("Coefficient: ");
    while(get_integer(&c) == 1){
        printf("Wrong input. Try again.\n\t");
    }
    list = delete_coeff(list, c);
    printf("New polynomial: ");
    print_list(list);
    delete_list(list);
    return 0;
}