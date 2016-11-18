#include<stdio.h>

int main(void){
    int indent_level = 0;
    int width = 5;
    int depth = 5;
    for (indent_level; indent_level < depth - 1; indent_level ++){
        for (int i = 0; i < indent_level; i++){
            printf(" ");
        }
        for (int i = 0; i < width; i++){
            printf("*");
        }
        printf("\n");
    }
    for (indent_level; indent_level >= 0; indent_level --){
        for (int i = 0; i < indent_level; i++){
            printf(" ");
        }
        for (int i = 0; i < width; i++){
            printf("*");
        }
        printf("\n");
    }
}
