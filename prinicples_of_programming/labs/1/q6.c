/*
 * Author: Amartya Vadlamani
 * Notes: More trig! How fun....
 */
#include <math.h>

#include "graphics.h"

void drawCircumscribedSquare(int x, int y, int radius){
    /*
     * Pythagorus thm. => a^2 + b^2 = c^2
     * given a, b are sides of a square, a == b
     * => 2 a^2 = c^2
     * c = diameter = 2*radius
     * => 2 a^2 = 4*r^2
     * => a^2 = 2 r^2
     * => a = sqrt(2) r
     */
    int square_width = sqrt(2) * radius;
    drawArc(x,y,2*radius,2*radius,0,360);
    int square_center_x = x + radius;
    int square_center_y = y + radius;
    drawRect(square_center_x - (int)(square_width/2),
             square_center_y - (int)(square_width/2),
             square_width,
             square_width);
}

int main (void){
    //for(int i = 1; i <= 5; i++){
    drawCircumscribedSquare(150, 150, 20);
    //}
}
