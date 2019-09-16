//
// Created by Dima on 18.05.2019.
//

#ifndef LAB12_TREE_AND_LIST_H
#define LAB12_TREE_AND_LIST_H

#include <string.h>
#include <errno.h>


typedef struct tree_NODE {
    struct tree_NODE *parent;
    struct tree_NODE *left;
    struct tree_NODE *right;
    char *word;
    int amount;
    short int last;
} pTreeNODE;

typedef pTreeNODE* treeNode;

typedef struct list_NODE {
    struct list_NODE* prev;
    struct list_NODE* next;
    treeNode value;
} pListNODE;

typedef pListNODE* listNode;

typedef struct {
    listNode head;
    listNode tail;
} pNODEList;

typedef pNODEList* List;

typedef struct {
    treeNode root;
} pTree;

typedef pTree* Tree;

Tree create_tree(char** words, int size);
void delete_tree(Tree tree);

List append(List list, treeNode value);
void delete_list(List list);

void print_tree_width(Tree);
void print_tree_height(Tree, int);

char* task(Tree tree);
#endif //LAB12_TREE_AND_LIST_H
