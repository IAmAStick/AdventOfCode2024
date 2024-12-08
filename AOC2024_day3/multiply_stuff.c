#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* file;


int multi_p1(char* input){

    char *current = input;
    int a, b;
    char comma, right_br;
    int final=0;

    current = strstr(current, "mul(");

    while(current){
        if(sscanf(current, "mul(%d%c%d%c", &a, &comma, &b, &right_br) == 4 && (comma == ',') && (right_br == ')')){
            final += a * b;
        }
        current++;
        current = strstr(current, "mul(");
    }
    return(final);
}

int multi_p2(char *input){

    char *main_text = input;
    char *current = NULL;
    char *do_command = NULL;
    char *dont_command = NULL;
    int a, b;
    char comma, right_br;
    int final = 0;

    current = strstr(main_text, "mul(");

    int do_or_not = 1;

    while(current){
        do_command = strstr(main_text, "do()");
        dont_command = strstr(main_text, "don't()");

        if(do_command && do_command < current){
            do_or_not = 1;
        }

        if(dont_command && dont_command < current){
            do_or_not = 0;
        }

        if(do_or_not){
            if(sscanf(current, "mul(%d%c%d%c", &a, &comma, &b, &right_br) == 4 && (comma == ',') && (right_br == ')')){
                final += a * b;
            }
        }
        current++;
        main_text = current;
        current = strstr(current, "mul(");
    }
    return(final);
}

int main()
{
    file = fopen("test.txt", "r");
        if (file == NULL) {
            printf("Error: Could not open file %s\n", "list_day1_1.txt");
            return 1;
        }

    fseek(file, 0, SEEK_END);
    int size_of_file = ftell(file);
    rewind(file);

    char *stuff = (char *)calloc(size_of_file+1,(sizeof(char)));

    fread(stuff, sizeof(char), size_of_file, file);
    fclose(file);

    int result = multi_p2(stuff);
    printf("result: %d", result);

    free(stuff);
    stuff = NULL;
}