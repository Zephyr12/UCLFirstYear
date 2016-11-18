#include<stdio.h>
#define MAX 6


int main(void){

    for (int i = 0; i < MAX; i ++){
        for (int y = 0; y < MAX; y++){
            if (y < i){
                printf(" ");
            }else{
                printf("*");
            }
        }
        printf("\n");
    }
}
