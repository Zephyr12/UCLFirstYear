#include<stdio.h>

int main(void){
    int current_times = 13;
    for (int current_val = 1; current_val <= current_times; current_val++){
        printf("%i * %i = %i\n", current_val, current_times , current_val * current_times);
    }
}
