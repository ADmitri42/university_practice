//
// Created by Dima on 11.03.2019.
//
#include <stdio.h>
#include "database.h"

int main(){
    init_index();
    print_table();
    printf("\n");
    print_index();
    delete_index();
    return 0;
}
