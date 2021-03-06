#include "graphics.h"
#include <math.h>

int getY(int x, int amplitude, float offset, float scaleFactor){
    return (int)(amplitude * sin(x * scaleFactor + offset));
}

void plotSine(int y, int amplitude, float offset, float scaleFactor, int quality){
    for (int x = 0; x < 1920; x += quality){
        // 1920 is the width of a standard wide screen shot
        int yval = getY(x, amplitude, offset, scaleFactor);
        int nextX = x + quality;
        int nextY = getY(nextX, amplitude, offset, scaleFactor);
        drawLine(x, yval+y, nextX, nextY+y);
    }
}

int main(void){
    plotSine(150, 100, 0, 0.05, 1);
}
