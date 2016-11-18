#include<stdio.h>

int exp_iter(int x, int y){
    int z = 1;
    for(int i = 0; i<y; i++){
        z *= x;
    }
    return z;
}

int exp_recur(int x, int y){
    return y ? x * exp_recur(x, y-1) : 1;
}

int main(void){
    int a = 5;
    int b = 4;
    printf(
            "%i ^ %i == %i (iter) || %i (recur)\n",
            a,
            b,
            exp_iter(a,b),
            exp_recur(a,b)
            );
    return 0;
}
