#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// #include <errno.h>
#include "utilities.h"
#include "text.h"
#include "binaries.h"


int main(){
    int size, new_size;
    double *data;
    char **strings;
    switch(menu()){
        case 1:
            data = get_array(&size);
            if (create_file_A("ready", data, size)){
                system("PAUSE");
                return 1;
            }
            free(data);
            if (read_file_A("ready", &data, &size)){
                system("PAUSE");
                return 1;
            }
            print_array(data, size);

            evaluate_A(&data, &size);

            if (create_file_A("ready2", data, size)){
                system("PAUSE");
                return 1;
            }
            free(data);
            if (read_file_A("ready2", &data, &size)){
                system("PAUSE");
                return 1;
            }
            printf("Answer(from file \'ready2\'): ");
            print_array(data, size);
            free(data);
            system("PAUSE");
            break;

        case 2:
            strings = get_strings(&size);
			if (strings == NULL) {
				system("PAUSE");
				return 1;
			}
            printf("%d\n", size);
            print_strings(strings, size);
            char** new_strings = evaluate_B(strings, size, &new_size);
            if (create_file_B("ready1.txt", new_strings, new_size)){
                system("PAUSE");
                return 1;
            }
            print_strings(new_strings, new_size);
			system("PAUSE");
			char** term = NULL;
			free(new_strings);
			if (size > 0) {
				term = strings[0];
			}
			free(strings);
//            if (read_file_A("ready2.txt", &data, &size)){
//                system("PAUSE");
//                return 1;
//            }

    }
    return 0;
}

