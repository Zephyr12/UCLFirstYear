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
    int p;
    scanf("%i", &p);
    printf("%i is", p);
    if (!is_prime(p)){
        printf("n't");
    }
    printf(" prime");
}
