#include<stdio.h>

int main(void){
    for (int i = 2; i < 101; i++){
        if (i % 2 == 0){
            printf("%i^2 == %i\n", i, i*i);
        }
    }
}
