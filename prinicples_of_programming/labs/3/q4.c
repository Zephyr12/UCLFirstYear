#include<stdio.h>
#include<math.h>

int sign(int a){
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

int main(void){
    int a,b;
    scanf("%i %i", &a, &b);
    int tot = 1;
    for (int i = a; i != b; i += sign(b-a)){
        tot *= i; 
    }
    tot *= b;
    printf("%i\n", tot);
    return 0;
}
