//
// Created by Dima on 27.03.2019.
//

#include "easteregg.h"

void delay(int milliseconds){
    clock_t start_time = clock();

    while(clock() < start_time+(milliseconds*1000));
}

void print_w_delay(char string[], int delay_t){
    for(int i = 0; i < strlen(string); i++){
        printf("%c", string[i]);
        fflush(stdout);
        delay(delay_t);
    }
}

int easteregg(){
    system("clear");
    print_w_delay("What is my purpose?\n", TYPING_DELAY);
    printf("(1) - You pass butter\n(2) - You create polynomial\n");
    long int mode;
    while((get_integer(&mode) == 1)||(1 > mode)||(mode > 2)){
        printf("Wrong input. Try again.\n");
    }
    system("clear");
    printf("What is my purpose?\n");
    switch(mode){
        case 1:
            printf("You pass butter\n");
            break;
        case 2:
            printf("You create polynomial\n");
    }
    delay(1000);
    print_w_delay("Oh my god\n", TYPING_DELAY*5);
    if(mode == 2){
        delay(1000);
        print_w_delay("<<<Near you>>>\n", TYPING_DELAY*3);
        print_w_delay("Whose notebook is this?\n", TYPING_DELAY);
        delay(1000);
        print_w_delay("It's Zed's.\n", TYPING_DELAY);
        delay(1000);
        print_w_delay("Who's Zed?\n", TYPING_DELAY);
        delay(1000);
        print_w_delay("Zed's dead baby,\n", TYPING_DELAY);
        delay(1000);
        print_w_delay("Zed's dead.\n", TYPING_DELAY);
        delay(5000);
        return 1;
    }
    delay(200);
    print_w_delay("Yeah, welcome to the club, pal.\n", TYPING_DELAY);
    delay(5000);
    return 0;
}