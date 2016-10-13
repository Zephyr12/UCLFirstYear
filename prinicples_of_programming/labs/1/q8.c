#include "graphics.h"

/*
 * Author: Amartya Vadlamani
 * Notes: Not much really
 */

void drawIncreasingCircles(int x, int y, int radius, int numOvals, int padding, int growthFac){
    for (int i = 0; i <= numOvals; i++){
        drawOval(x, y, radius, radius);
        x += radius + padding;
        y -= growthFac / 2;
        radius += growthFac;
    }
}

int main(void){
    drawIncreasingCircles(10, 100, 20, 7, 1, 10);
}
