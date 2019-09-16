#include <stdio.h>
#include "dstdin.h"
#include "utilities.h"


int main() {
    int amount;
    char *string = get_string();
    for(int i=0; i<strlen(string);i++){
        if((string[i] == ' ')||(string[i] == '.')||(string[i] == '\n')){
            continue;
        }else if((string[i]>'a')&&(string[i]<'z')){
//            free(string);
            continue;
        }
        printf("I will never do it.\n");
        return 1;
    }
    char **words = get_words(string, &amount);
    if(amount < 0){
        return 1;
    }
    List list = NULL;
    for(int i = 0; i<amount; i++){
        list = append(list, words[i]);
    }
//    printf("%d", amount);
    free(words);
    free(string);
    print_sentence(list);
    printf("\n");
    long int max = max_lenght(list);
//    printf("%ld\n", max);
    list = magick(list, max);
    print_sentence(list);
    printf("\n");
    delete_list(list);
    return 0;
}