//
// Created by Dima on 11.03.2019.
//

#include "utilities.h"

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

char* change_length(char *string, int new_size){
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

int get_integer(){
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);
    int mode;
    while((sscanf(buffer, "%d", &mode) == 0)){
        printf("Wrong input. Try again.\n");
        fgets(buffer, BUFFER_SIZE, stdin);
    }
    return mode;
}

double get_double(){
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);
    double mode;
    while ((sscanf(buffer, "%lf", &mode) == 0)) {
        printf("Wrong input. Try again.\n");
        fgets(buffer, BUFFER_SIZE, stdin);
    }
    return mode;
}

int beautiful_string_get(char var_name[], char** var){
    printf("%s: ", var_name);
    *var = get_string();
    if(*var == NULL){
        return 1;
    }
    *var = change_length(*var, NAME_LENGHT);
    if(*var == NULL){
        return 1;
    }
    char* new_line = strchr(*var, '\n');
    if(new_line != NULL){
        *new_line = 0;
    }
    return 0;

}

int select_field(int w_taxes){
    printf("1 - name\n2 - surname\n3 - patronymic\n4 - department\n5 - salary\n6 - prizes\n");
    int mode, max = 6;
    if(w_taxes){
        printf("7 - taxes\n");
        max++;
    }
    printf("0 - exit\n");
    while(((mode = get_integer()) < 0)||(mode > max)){
        printf("Wrong input. Try again.\n");
    }
    mode--;
    return mode;
}

Person get_person_stdin_(){
    Person person;
    char *name, *surname, *patern, *depart;
    double salary, prizes;
    if(beautiful_string_get("Name", &name)){
        return NULL;
    }
    if(beautiful_string_get("Surname", &surname)){
        free(name);
        return NULL;
    }
    if(beautiful_string_get("Patronymic", &patern)){
        free(name);
        free(surname);
        return NULL;
    }
    if(beautiful_string_get("Department", &depart)){
        free(name);
        free(surname);
        free(patern);
        return NULL;
    }
    printf("Salary: ");
    salary = get_double();
    printf("Prizes: ");
    prizes = get_double();

    person = create_person(name, surname, patern, depart, salary, prizes);
    return person;
}

void greetings(){
    printf("Welcome to bookkeeping database manager.\n");
}

int menu(){
    int mode;
    printf("\n1 - create new record\n2 - find record\n3 - delete record\n4 - edit record\n5 - sort records\n6 - show table\n0 - exit\n");
    while(((mode = get_integer()) < 0)||(mode > 6)){
        printf("Wrong input. Try again.\n");
    }
    return mode;
}

Person get_person_stdin(){
    Person person;
    system("clear");
    printf("Welcome to account creator. I'll help you with creating of a profile for worker. ");
    printf("You need to fill in some fields, rest of the work I'll handle myself.\n");
    printf("Remember that we cannot fit names with length greater that %d symbols. Sorry:)\n", NAME_LENGHT - 1);

    person = get_person_stdin_();
    if(person == NULL) {
        return NULL;
    }
    printf("That's all. Here's new person in database.\n");
    print_person(person);
    return person;
}

List search(){
    printf("By which field?\n");
    int field = select_field(1);
    char *val;
    double sal;
    List persons;
    if(field<0){
        persons = NULL;
    } else if(field < 4){
        printf("Value: ");
        val = get_string();
        val[strlen(val) - 1] = 0;
        persons = find(val, field);
        free(val);
    } else {
        printf("Value: ");
        sal = get_double();
        persons = find(&sal, field);
    }
    return persons;
}

int real_search(){
    system("clear");
    printf("Welcome to search. I'll help you with search of records.\n");
    printf("You need to specify field and value, rest of the work I'll handle myself.\n");
    printf("Remember that we cannot fit names with length greater that %d symbols. Sorry:)\n", NAME_LENGHT - 1);
    List persons = search();
    if(persons == NULL){
        return 0;
    } else if(persons->size == 0){
        printf("No one meets your requirements\n");
    } else {
        print_persons(persons);
    }
    delete_list(persons);
    return 0;
}

int delete_record(){
    system("clear");
    printf("Welcome to delete manager. I'll help you with deleting.\n");
    printf("At the beginning we need to find record. You need to specify field and value.\n");
    printf("Remember that we cannot fit names with length greater that %d symbols. Sorry:)\n", NAME_LENGHT - 1);
    int ind;
    Person person;
    List persons = search();
    if(persons == NULL){
        return 0;
    } else if(persons->size == 0){
        printf("No one meets your requirements\n");
    } else {
        print_persons(persons);
        printf("Who you wanna delete? Specify place in table above. ");
        while(((ind = get_integer()) < 0)||(ind >= persons->size)){
            printf("Wrong input. Try again.\n");
        }
        printf("Now I'll destroy him.\n");
        person = get_person_by_position(persons->data[ind]);
        drop_from_table(person);
        free_person(person);
        printf("Now he is gone.\n");
    }
    delete_list(persons);
}

int sort_records(){
    system("clear");
    printf("Welcome to sorting manager. I'll help you with deleting.\n");
    printf("At the beginning we need to understand by which field.\n");
    int field = select_field(1);
    if(field < 0){
        return 0;
    }
    List persons = sort(field);
    if(persons == NULL){
        return 0;
    } else if(persons->size == 0){
        printf("No records\n");
    } else {
        print_persons(persons);
    }
    delete_list(persons);
}

int edit_record(){
    system("clear");
    printf("Welcome to editor manager. I'll help you with editing.\n");
    printf("At the beginning we need to find record. You need to specify field and value.\n");
    printf("Remember that we cannot fit names with length greater that %d symbols. Sorry:)\n", NAME_LENGHT - 1);
    int ind;
    Person person;
    List persons = search();
    if(persons == NULL){
        return 0;
    } else if(persons->size == 0){
        printf("No one meets your requirements\n");
    } else {
        print_persons(persons);
        printf("Who you wanna edit? Specify place in table above. ");
        while(((ind = get_integer()) < 0)||(ind >= persons->size)){
            printf("Wrong input. Try again.\n");
        }
        printf("Here's he.\n");
        person = get_person_by_position(persons->data[ind]);
        print_person(person);
        printf("Which field?");
        int field = select_field(0);
        if(field < 0){
            return 0;
        }

        char *val;
        double c;
        if(field < 4){
//            val = get_string();
            if(beautiful_string_get("New value", &val)){
                free_person(person);
                delete_list(persons);
                return 1;
            }
//            free(val);
//            val[strlen(val)-1] = 0;
        } else {
            printf("New value: ");
            c = get_double();
        }
        switch(field){
            case 0:
                stpncpy(person->name, val, NAME_LENGHT);
                break;
            case 1:
                stpncpy(person->surname, val, NAME_LENGHT);
                break;
            case 2:
                stpncpy(person->patronymic, val, NAME_LENGHT);
                break;
            case 3:
                stpncpy(person->department, val, NAME_LENGHT);
                break;
            case 4:
                person->salary = c;
                person->taxes = (person->salary + person->prizes)*0.13;
                break;
            case 5:
                person->prizes = c;
                person->taxes = (person->salary + person->prizes)*0.13;
                break;
        }
        save_person(person);
        free_person(person);
    }
    delete_list(persons);
}