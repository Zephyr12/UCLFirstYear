#include<math.h>
#include "graphics.h"

int main(void){
        float old_x = 0;
        float old_y = 0;
    for (float t = 0; t <= M_PI*100; t += 0.01){
        float rad = sqrt(t*1000);
        float x = sin(t) * rad;
        float y = cos(t) * rad;
        drawLine(old_x+250,old_y+150,x+250,y+150);
        old_x = x;
        old_y = y;
    }
}
