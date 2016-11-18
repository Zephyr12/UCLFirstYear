#include<stdio.h>

int main(void){
    int width = 6;
    int height = 6;
    for(int line = 0; line < height; line++){
        for(int c = 0; c < width; c++){
            char* output = "*#";
            if (line % 2 == 1){
                output = "#*";
            }
            printf("%c", output[c%2]);
        }
        printf("\n");
    }
}
