//
// Created by Dima on 12.03.2019.
//

#include <stdio.h>
#include "database.h"
#include "utilities.h"

int main(){
    init_index();
    Person person = get_person_stdin();
    free_person(person);
    delete_index();
    return 0;
}