//
// Created by Dima on 18.05.2019.
//

#include "tree_and_list.h"
#include <malloc.h>

char* copy(const char *s1)
{
    const size_t len1 = strlen(s1);
    char *result = malloc(len1 + 1); // +1 for the null-terminator
    if(result == NULL){
        perror(strerror(errno));
        return NULL;
    }
    memcpy(result, s1, len1+1);
    return result;
}

treeNode create_node(char *word){ // Create new node
    treeNode node = malloc(sizeof(pTreeNODE));
    if(node == NULL){
        perror(strerror(errno));
        return NULL;
    }
    node->amount = 1;
    node->last = 0;
    node->word = copy(word);
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

treeNode add_word(treeNode root, char *word){
    treeNode next_node = NULL;
    int r;
    if(root == NULL){
        root = create_node(word);
    }else {
        if((r = strcmp(root->word, word)) > 0){
            next_node = add_word(root->right, word);
            root->right = next_node;
            if(next_node == NULL){
                return NULL;
            }
            next_node->parent = root;
        } else if(r < 0){
            next_node = add_word(root->left, word);
            root->left = next_node;
            if(next_node == NULL){
                return NULL;
            }
            next_node->parent = root;
        } else {
            root->amount++;
        }

    }
    return root;
}

Tree create_tree(char** words, int size){
    Tree tree = malloc(sizeof(pTree));
    if(tree == NULL){
        perror(strerror(errno));
        return NULL;
    }
    tree->root = NULL;
    for(int i = 0; i < size; i++){
        tree->root = add_word(tree->root, words[i]);
        if(tree->root == NULL){
            delete_tree(tree);
            return NULL;
        }
    }
    return tree;
}

void delete_tree_nodes(treeNode root){
    if(root != NULL){
        delete_tree_nodes(root->left);
        delete_tree_nodes(root->right);
        free(root);
    }
}

void delete_tree(Tree tree){
    if(tree != NULL){
        if(tree->root != NULL){
            delete_tree_nodes(tree->root);
        }
        free(tree);
    }
}

List append(List list, treeNode value){
    if(list == NULL){
        list = malloc(sizeof(pListNODE));
        if(list == NULL){
            return NULL;
        }
        list->head = NULL;
        list->tail = NULL;
    }
    if(value == NULL){
        return list;
    }
    listNode new_node = malloc(sizeof(pListNODE));

    new_node->value = value;
//    new_node->size = strlen(value);
//    strcpy(new_node->value, value);

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

List appbeg(List list, treeNode value){
    if(list == NULL){
        list = malloc(sizeof(pListNODE));
        if(list == NULL){
            return NULL;
        }
        list->head = NULL;
        list->tail = NULL;
    }
    if(value == NULL){
        return list;
    }
    listNode new_node = malloc(sizeof(pListNODE));

    new_node->value = value;
//    new_node->size = strlen(value);
//    strcpy(new_node->value, value);

    new_node->next = NULL;
    new_node->prev = NULL;
    if(list->tail == NULL){
        list->tail = new_node;
    }
    if(list->head != NULL){
        new_node->next = list->head;
        new_node->next->prev = new_node;
    }
    list->head = new_node;
//    if(list->head == NULL){
//        list->head = list->tail;
//    }
    return list;
}

List remove_first(List list){
    listNode node = list->head;
    if(node != NULL){
        if(list->head == list->tail){
            list->tail = NULL;
            list->head = NULL;
        } else {
            list->head = list->head->next;
        }
        free(node);
    }
    return list;

}

void delete_list(List list){
    if(list != NULL){
        listNode node;
        while(list->head != NULL){
            node = list->head;
            if(node == list->tail){
                list->tail = NULL;
            }
            list->head = list->head->next;
            free(node);
        }
        free(list);
    }
}

void print_tree_width(Tree tree){
    List current_level = NULL;
//    List next_level = NULL;
    listNode node = NULL;
    int notnull = 1;
    if(tree->root != NULL){
        current_level = append(current_level, tree->root);
        while(current_level->head != NULL){
            node = current_level->head;
            fputs(node->value->word, stdout);
            printf(" ");
            current_level = append(current_level, node->value->left);
            current_level = append(current_level, node->value->right);
            current_level = remove_first(current_level);
        }

    }else{
        printf("Empty tree\n");
    }
    printf("\n");
}

void print_nodes1(treeNode node){
    if(node != NULL){
        fputs(node->word, stdout);
        printf(" ");
        print_nodes1(node->left);
        print_nodes1(node->right);
    }
}

void print_nodes2(treeNode node){
    if(node != NULL){
        print_nodes2(node->left);
        fputs(node->word, stdout);
        printf(" ");
        print_nodes2(node->right);
    }
}

void print_nodes3(treeNode node){
    if(node != NULL){
        print_nodes3(node->left);
        print_nodes3(node->right);
        fputs(node->word, stdout);
        printf(" ");
    }
}

void print_tree_height(Tree tree, int sol){
//    int notnull = 1;
    if(tree->root != NULL){
        switch(sol){
            case 1:
                print_nodes1(tree->root);
                break;
            case 2:
                print_nodes2(tree->root);
                break;
            case 3:
                print_nodes3(tree->root);
                break;
        }
    }else{
        printf("Empty tree\n");
    }
    printf("\n");
}

treeNode task_node(treeNode node){
    if(node == NULL){
        return NULL;
    }
    treeNode left, right, max;
    left = task_node(node->left);
    right = task_node(node->right);
    if(left == NULL){
        max = right;
    } else if(right == NULL){
        max = left;
    } else if(left->amount >= right->amount){
        max = left;
    } else {
        max = right;
    }
    if(max != NULL){
        if(max->amount >= node->amount){
            return max;
        } else {
            return node;
        }
    } else {
        return node;
    }
}

char* task(Tree tree){
    treeNode node;
    node = task_node(tree->root);
    return copy(node->word);
}


