#include <stdio.h>
#include "database.h"
#include "utilities.h"

int main(){
     init_index();
     greetings();
     Person person;
     int mode;
     while(mode = menu()){
         switch(mode){
             case 1:
                 free_person(get_person_stdin());
                 break;
             case 2:
                 real_search();
                 break;
             case 3:
                 delete_record();
                 break;
             case 4:
                 edit_record();
                 break;
             case 5:
                 sort_records();
                 break;
             case 6:
                 print_table();
                 break;
         }
     }
     delete_index();
     return 0;
}