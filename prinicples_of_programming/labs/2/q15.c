#include<stdio.h>
#define MAX 26

void draw_rect(int x, int y, char c){
    for (int i = 0; i < y; i++){
        for (int j = 0; j < x; j++){
            printf("%c ", c);
        }
        printf("\n");
    }
}

int main(void){
    for(int i = 1; i <= MAX; i++){
        draw_rect(i, MAX + 1 - i,*("!\"£$%^&*(){}:@~<>?|\\,./;'#[]-=+_" + i - 1)); // yay for full pointer dereferencing a.k.a C pointer magic
    }
}
