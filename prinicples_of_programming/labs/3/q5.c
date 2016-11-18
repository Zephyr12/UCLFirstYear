#include<string.h>
#include<stdio.h>
#include<stdlib.h>

char* nineteen(int a){
    char *arr[] = {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
        "ten",
        "eleven",
        "twelve",
        "thirteen",
        "fourteen",
        "fifteen",
        "sixteen",
        "seventeen",
        "eighteen",
        "nineteen"
    };

    return arr[a];
}

char* ninetynine(int a){
    if (a<=19){
        return nineteen(a);
    }
    char *tens_arr[] = {
        "zero",
        "ten",
        "twenty",
        "thirty",
        "forty",
        "fifty",
        "sixty",
        "seventy",
        "eighty",
        "ninety"
    };
    char* tens = tens_arr[a/10];
    char* units = nineteen(a%10);
    char* result = malloc(30);
    if (a%10 != 0){
        sprintf(result, "%s %s", tens, units);
    }else{
        sprintf(result, "%s", tens);
    }
    return result;
}

char* ninehundredandnintynine(int a){
    if (a <= 99){
        return ninetynine(a);
    }
    char* result = malloc(1000);
    sprintf(result, "%s hundred and %s", nineteen(a/100), ninetynine(a%100));
    return result;
}

int main(void){
    int a;
    scanf("%i", &a);
    printf("%s\n", ninehundredandnintynine(a));
}
