#include<stdio.h>

int main(void){
    int width = 8;
    int height = 7;
    for(int x = 0; x < height; x ++){
        for(int y = 0; y < width; y ++){
            if (x >= height - 1 || x < 1 || y >= width - 1 || y < 1){
                printf("*");
            }else if (x >= 2 && x <= height - 3 && y > 1 && y <= width - 3 && !(x == 3 && (y ==3 || y == 4))){
                printf("#");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
