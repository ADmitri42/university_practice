#ifndef LAB9_DATABASE_H
#define LAB9_DATABASE_H

//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>

#ifndef NAME_LENGHT
#define NAME_LENGHT 100
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 200
#endif

#define DATABASEFILE "bookkeepingdata"
#define INDEXFILE "indexdata"
#define STEPSIZE 10
#define GAP 0.01

//#define add_head(...) add_head_args((f_args){__VA_ARGS__});

extern int errno;

typedef struct {
    long int *position;
    int *state;
    int size;
    int max_size;
} pIndex;

typedef struct {
    char name[NAME_LENGHT];
    char surname[NAME_LENGHT];
    char patronymic[NAME_LENGHT];
    char department[NAME_LENGHT];
    double salary;
    double prizes;
    double taxes;
    long int position;
}  pPerson;

typedef struct {
    long int *data;
    int size;
    int max_size;
} pList;

typedef pPerson* Person;
typedef pList* List;

void init_index();
void print_index();
void delete_index();
void save_index();

void set_index_state();
int get_index_state(long int position);
long int get_empty_cell();


void delete_list(List list);


Person create_person(char *name, char *surname, char *patronymic, char *department, double salary, double prizes);
void print_person(Person person);
void print_persons(List persons);
Person get_person_by_position(long int position);
List get_persons();
List find(void *value, int field);
void drop_from_table(Person person);
void free_person(Person person);
int save_person(Person);

List sort(int field);

void print_table();
#endif //LAB9_DATABASE_H
