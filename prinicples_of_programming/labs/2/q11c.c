#include<stdio.h>
#include<stdbool.h>
#include<math.h>

bool is_prime(int p){
    if (p < 2){
        return false;
    }
    for (int t = 2; t < (int)(sqrt(p)) + 1; t++){
        if (p % t == 0){
            return false;
        }
    }
    return true;
}

int main(void){
    for (int i = 1; i <= 100; i++){
        char* is_prime_string = is_prime(i) ? "is": "isn't";
        printf("%i %s prime\n", i, is_prime_string);
    }
}
