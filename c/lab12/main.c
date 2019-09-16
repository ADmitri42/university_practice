#include <stdio.h>
#include "dstdin.h"
#include "tree_and_list.h"

int main() {
    int amount;
    char *w, *string = get_string();
    char **words = get_words(string, &amount);
    if(amount < 0){
        return 1;
    }
    for(int i = 0; i < amount; i++){
        if(strlen(words[i]) > 20){
            printf("Word \"");
            fputs(words[i], stdout);
            printf("\" is too long\n");
            free(string);
            free(words);
            return 1;
        }
    }
    Tree tree = create_tree(words, amount);
    free(string);
    free(words);
    printf("Width...\n");
    print_tree_width(tree);
    printf("Height 1...\n");
    print_tree_height(tree, 1);
    printf("Height 2...\n");
    print_tree_height(tree, 2);
    printf("Height 3...\n");
    print_tree_height(tree, 3);
    printf("Answer\n\t");
    w = task(tree);
    if(strlen(w) == 0){
        printf("Did you know that you have empty word in your list?\n");
    } else {
        fputs(w, stdout);
        printf("\n");
    }
    free(w);
    delete_tree(tree);
    return 0;
}