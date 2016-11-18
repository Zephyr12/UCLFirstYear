#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#include<string.h>
#include<math.h>
#define MAX_STR_SIZE 1024
bool is_palindrome(char* s, int length){
    for (int i = 0; i < length; i++){
        int y = length - i - 1;
        if (s[i] != s[y]){
            return false;
        }
    }
    return true;
}
bool is_int(char* s, int length){
    for (int i = 0; i < length; i++){
        if (s[i] < '0' || s[i] > '9'){
            return false;
        }
    }
    return true;
}

int main(void){
    char* s = malloc(MAX_STR_SIZE);
    scanf("%s", s);
    int l = strlen(s);
    if(is_int(s,l)){
        if (is_palindrome(s,l)){
            printf("%s is a palindrome\n", s);
        }
        else{
            printf("%s isn't a palindrome\n", s);
        }
    }else{
        printf("%s isn't a number\n", s);
    }
}
