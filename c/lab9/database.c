#include "database.h"

//extern int errno;
static pIndex *dbindex = NULL;

void init_index(){
    dbindex = malloc(sizeof(pIndex));
    FILE *f = fopen(INDEXFILE, "rb");
    if (f == NULL){
        dbindex->position = calloc(STEPSIZE, sizeof(long int));
        dbindex->state = calloc(STEPSIZE, sizeof(int));
        dbindex->size = 0;
        dbindex->max_size = STEPSIZE;
    } else {
        fread(&(dbindex->size), sizeof(int), 1, f);
        dbindex->position = calloc(dbindex->size, sizeof(long int));
        dbindex->state = calloc(dbindex->size, sizeof(int));
        dbindex->max_size = dbindex->size;
        for(int i = 0; i<dbindex->size;i++){
            fread(dbindex->position + i, sizeof(long int), 1, f);
            fread(dbindex->state + i, sizeof(int), 1, f);
        }
        fclose(f);
    }
}

void print_index(){
    if(dbindex == NULL){
        printf("Index is not initialized\n");
    } else {
        printf("Position | State\n------------------------\n");
        for(int i = 0; i < dbindex->size; i++){
            printf("%ld\t |\t%d\n", dbindex->position[i], dbindex->state[i]);
        }
    }
}

void delete_index(){
    free(dbindex->position);
    free(dbindex->state);
    free(dbindex);
    dbindex = NULL;
}

void save_index(){
    FILE *f = fopen(INDEXFILE, "wb");
    if (f == NULL){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    }else {
        fwrite(&dbindex->size, sizeof(int), 1, f);
        for(int i = 0; i<dbindex->size;i++){
            fwrite(dbindex->position + i, sizeof(long int), 1, f);
            fwrite(dbindex->state + i, sizeof(int), 1, f);
        }
        fclose(f);
    }
}

void set_index_state(long int position, int state){
    int place = -1;
    for(int i = 0; i<dbindex->size; i++){
        if(dbindex->position[i] == position){
            place = i;
            break;
        }
    }
    if(place < 0){
        if(dbindex->max_size <= dbindex->size+1){
            dbindex->max_size += STEPSIZE;
            dbindex->position = realloc(dbindex->position, dbindex->max_size*sizeof(long int));
            dbindex->state = realloc(dbindex->state, dbindex->max_size*sizeof(int));
        }
        dbindex->position[dbindex->size] = position;
        dbindex->state[dbindex->size] = state;
        dbindex->size++;
    } else {
        dbindex->state[place] = state;
    }
    save_index();
}

int get_index_state(long int position){
    int place = -1, state = 0;
    for(int i = 0; i<dbindex->size; i++){
        if(dbindex->position[i] == position){
            place = i;
            break;
        }
    }
    if(place>=0){
        state = dbindex->state[place];
    }
    return state;
}

long int get_empty_cell(){
    long int place = -1;
    for(int i = 0; i<dbindex->size; i++){
        if(dbindex->state[i] == 0){
            place = dbindex->position[i];
            break;
        }
    }
    return place;
}


/*******************************
 * Delete list
 *  list
 */
void delete_list(List list){
    free(list->data);
    free(list);
}

/*******************************
 * This function create person in database
 *  name
 *  surname
 *  patronymic
 *  department
 *  salary
 *  prizes
 *  person instance
 */
Person create_person(char *name, char *surname, char *patronymic, char *department, double salary, double prizes){

    Person item = malloc(sizeof(pPerson));
    stpncpy(item->name, name, NAME_LENGHT);
    stpncpy(item->surname, surname, NAME_LENGHT);
    stpncpy(item->patronymic, patronymic, NAME_LENGHT);
    stpncpy(item->department, department, NAME_LENGHT);

    item->salary = salary;
    item->prizes = prizes;

    item->taxes = (salary+prizes)*0.13;
    item->position = -1;
    if(save_person(item)){
        free_person(item);
        item = NULL;
    }
    return item;
    }

/*************************
 * Save person to database
 *  person
 *  0 - if everything is ok
 */
int save_person(Person person){
    FILE *f = fopen(DATABASEFILE, "r+b");
    if (f == NULL){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return errno;
    }
    if(person->position >= 0){
        fseek(f, person->position, SEEK_SET);
    } else {
        long int position = get_empty_cell();
        if(position < 0){
            person->position = ftell(f);
        } else {
            fseek(f, position, SEEK_SET);
            person->position = position;
        }
    }
    fwrite(person, sizeof(pPerson), 1, f);
    set_index_state(person->position, 1);
    fclose(f);
}

void print_person(Person person){
//    fputs(person->name, stdout);
//    printf(" ");
//    fputs(person->surname, stdout);
//    printf(" ");
//    fputs(person->patronymic, stdout);
//    printf("\t|\t");
//    fputs(person->department, stdout);
//    printf("\t|\t%.2lf\t|\t%.2lf\t|\t%.2lf\n", person->salary, person->prizes, person->taxes);
    printf("%s %s %s\t\t|\t%-10s\t|\t%7.2lf\t|\t%7.2lf\t|\t%7.2lf\n", person->name, person->surname, person->patronymic, person->department, person->salary, person->prizes, person->taxes);
}

void print_persons(List persons){
    Person person;
    for(int i = 0; i < persons->size; i++){
        person = get_person_by_position(persons->data[i]);
        printf("%-4d|", i);
        print_person(person);
        free_person(person);
    }
}

Person get_person_by_position(long int position){
    if(get_index_state(position) == 0){
        return NULL;
    }
    Person person = malloc(sizeof(pPerson));
    FILE *f = fopen(DATABASEFILE, "rb");
    if (f == NULL){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return NULL;
    }
    fseek(f, position, SEEK_SET);
    fread(person, sizeof(pPerson), 1, f);
    fclose(f);
    return person;
}

List get_persons(){
    List persons = malloc(sizeof(pList));
    persons->data = calloc(dbindex->size, sizeof(long int));
    persons->max_size = dbindex->size;
    persons->size = 0;
    for(int i = 0; i<dbindex->size; i++){
        if(dbindex->state[i]){
            persons->data[persons->size] = dbindex->position[i];
            persons->size++;
        }
    }
    return persons;
}


int suit_name(Person person, void *value){
    return !strcmp(person->name, value);
}

int suit_surname(Person person, void *value){
    return !strcmp(person->surname, value);
}

int suit_patron(Person person, void *value){
    return !strcmp(person->patronymic, value);
}

int suit_depart(Person person, void *value){
    return !strcmp(person->department, value);
}

int suit_salary(Person person, void *value){
    return (person->salary == *((double*)value));
}

int suit_prizes(Person person, void *value){
    return (person->prizes == *((double*)value));
}

int suit_taxes(Person person, void *value){
    return (person->taxes == *((double*)value));
}

static int (*suitable[7])(Person, void*) = {&suit_name, &suit_surname, &suit_patron, &suit_depart, &suit_salary, &suit_prizes, &suit_taxes};

List find(void *value, int field){
    Person person;
    List persons, suit_now;

    int (*suit)(Person, void*) = suitable[field];
    persons = get_persons();

    suit_now = malloc(sizeof(pList));
    suit_now->data = calloc(dbindex->size, sizeof(long int));
    suit_now->max_size = dbindex->size;
    suit_now->size = 0;
    for(int i = 0; i<persons->size; i++){
        person = get_person_by_position(persons->data[i]);
        if(suit(person, value)){
            suit_now->data[suit_now->size] = persons->data[i];
            suit_now->size++;
        }
        free_person(person);
    }
    delete_list(persons);
    return suit_now;
}

void drop_from_table(Person person){
    set_index_state(person->position, 0);
}

void free_person(Person person){
    free(person);
}

void print_table(){
    List persons = get_persons();
    printf("#   |\tName\t\t|\tDepartment\t|\tSalary\t\t|\tPrizes\t\t|\tTaxes\n");
    printf("------------------------------------------------------------------------------\n");
    print_persons(persons);
    delete_list(persons);
}

int change_name(Person a, Person b){
    return strcmp(a->name, b->name) > 0;
}

int change_surname(Person a, Person b){
    return strcmp(a->surname, b->surname) > 0;
}

int change_patron(Person a, Person b){
    return strcmp(a->patronymic, b->patronymic) > 0;
}

int change_depart(Person a, Person b){
    return strcmp(a->department, b->department) > 0;
}

int change_salary(Person a, Person b){
    return a->salary > b->salary;
}

int change_prizes(Person a, Person b){
    return a->prizes > b->prizes;
}

int change_taxes(Person a, Person b){
    return a->taxes > b->taxes;
}

static int (*change[7])(Person, Person) = {&change_name, &change_surname, &change_patron, &change_depart, &change_salary, &change_prizes, &change_taxes};

List sort(int field){
    int (*change_them)(Person, Person) = change[field];
    Person A, B;
    long int term;
    List persons = get_persons();
    int flag = 0;
    do{
        flag = 0;
        for(int i = 0; i < persons->size - 1; i++){
            A = get_person_by_position(persons->data[i]);
            B = get_person_by_position(persons->data[i+1]);
            if(change_them(A, B)){
                term = persons->data[i];
                persons->data[i] = persons->data[i+1];
                persons->data[i+1] = term;
                flag++;
            }
            free_person(A);
            free_person(B);
        }
    } while(flag);
    return persons;
}