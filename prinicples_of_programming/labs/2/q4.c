#include<stdio.h>

void line(int size){
    for (int i = 0; i < size; i++){
        printf("*");
    }
    printf("\n");
}

int main(void){
    line(5);
    for (int i = 1; i <= 5; i++){
        if (i % 2 == 0){
            printf("*");
            for (int y = 0; y < 3; y++){
                printf(" ");
            }
            printf("*");
        }else{
        }
        printf("\n");
    }
    line(5);
}
