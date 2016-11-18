#include<stdio.h>
#include<stdbool.h>
#include<math.h>

bool is_prime(int a){
    if (a<2){
        return false;
    }
    for (int i = 2; i <= sqrt((float)a); i++){
        if (a%i==0){
            return false;
        }
    }
    return true;
}

int main(void){
    int min_range, max_range;
    scanf("%i %i", &min_range, &max_range);
    for (int i = min_range+1; i <= max_range; i++){
        if (min_range <= 2 && max_range >= 3 && i == 3){
            printf("%i and %i aren't really twin primes but meh!\n", i-1, i);
        }
        if (is_prime(i-1) && is_prime(i+1)){
            printf("%i and %i are twin primes\n", i-1, i+1);
        }
    }
}
