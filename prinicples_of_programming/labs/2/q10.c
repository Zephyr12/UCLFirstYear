#include<stdio.h>

#define CHAR_A '*'
#define CHAR_B '#'

int main(void){
    int size_x = 7;
    int size_y = 8;

    for (int y = 0; y < size_y; y++){
        for (int x = 0; x < size_x; x++){
            char output = ' ';

            if (x == 0){
                output = CHAR_B;
            } // draw the right hand line of *

            if (x == size_x - 1){
                output = CHAR_A;
            } // draw the left hand line of #


            if (y - 1 == x){
                output = CHAR_B;
            } // draw the # diagonal line

            if (y == x){
                output = CHAR_A;
            } // draw the * diagonal line

            if (y == 0){
                output = CHAR_A;
            } // draw the top line

            if (y == size_y - 1){
                output = CHAR_B;
            } // draw the bottom line

            // otherwise fill it with a space
            printf("%c", output);
        }
        printf("%c", '\n');
    }
}
