#include<stdio.h>

int main(void){
    int indent_level = 0;
    int max_level = 4;
    for(indent_level; indent_level < max_level; indent_level++){
        for (int i = 0; i < indent_level + 1; i++){
            char output = ' ';
            if (i == 0 || i == indent_level){
                output = '*';
            }
            printf("%c", output);
        }
        printf("\n");
    }
    for (indent_level; indent_level >= 0; indent_level--){
        for (int i = 0; i < indent_level + 1; i++){
            char output = ' ';
            if (i == 0 || i == indent_level){
                output = '*';
            }
            printf("%c", output);
        }
        printf("\n");
    }
}
