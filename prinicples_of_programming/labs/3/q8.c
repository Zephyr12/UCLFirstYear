#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>

int digit_to_int(char digit){
    return (int)(digit-'0'); // yay for ascii
}

int factorial(int num){
    int tot = 1;
    for (int i = 1; i <= num; i++){
        tot *= i;
    }
    return tot;
}

int main(void){
    int min, max;
    scanf("%i %i", &min, &max);
    for (int i = min; i <= max; i++){
        char str[80];
        sprintf(str, "%i", i);
        int str_len = strlen(str);
        int fac_sum = 0;
        for (int y = 0; y < str_len; y++){
            char digit = str[y];
            fac_sum += factorial(digit_to_int(digit));
        }
        if (fac_sum == i){
            printf("%i is a strong number\n", i);
        }
    }
}
