#include<stdio.h>

int main(void){
    int current_val = 1;
    int current_times = 13;
    while (current_val <= current_times){
        printf("%i * %i = %i\n", current_val, current_times , current_val * current_times);
        current_val += 1;
    }
}
