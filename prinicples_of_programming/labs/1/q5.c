/*
 * Author: Amartya Vadlamani
 * Notes: Nothing Amazing Here...
 */

#include "graphics.h"

void drawRectWithLines(int x, int y, int w, int h){
    int points[4][2] = {
        {x, y},
        {x+w, y},
        {x+w, y+h},
        {x, y+h}
    };

    int draw_x = points[0][0];
    int draw_y = points[0][1];
    for (int point = 1; point < 4; point++){
        // I really dont want to unroll this loop manually
        int new_x = points[point][0];
        int new_y = points[point][1];

        drawLine(draw_x,draw_y,new_x,new_y);
        draw_x = new_x;
        draw_y = new_y;
    }
    drawLine(draw_x, draw_y, x, y);
}

int main (void){
    drawRectWithLines(30, 30, 90, 50);
    drawRect(150, 50, 60, 140);
    
}
