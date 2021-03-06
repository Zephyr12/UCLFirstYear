/*
 *
 * Author: Amartya Vadlamani
 * Notes: I know that the question only said to make a heptagon but I got bored
 *
 */

#include <math.h>

#include "graphics.h"

#define M_PI 3.14159265

void drawRegularNGon(int x, int y, int radius, int sides, float rotation){
    /* 
     * The angle between any two points on an regular NGon is equal to the
     * angle of a circle 2 Pi divided by the number of sides in the NGon
     */ 
    float angle = (2*M_PI)/((float)sides);

    int last_point_x = (int)(sin(angle*0 + rotation) * radius);
    int last_point_y = (int)(cos(angle*0 + rotation) * radius);

    for(int side=1; side <= sides; side++){
        /*
         * The <= is to ensure we reach the start vertex.
         * As this means that side takes values [1..sides].
         */ 

        /*
         * Using the standard trigonometric definitions we get
         */
        int new_point_x = (int) (sin(angle*side + rotation) * radius);
        int new_point_y = (int) (cos(angle*side + rotation) * radius);

        drawLine(last_point_x + x, // The +x and +y are to transform the
                 last_point_y + y, // coordinates from local to world
                 new_point_x + x,  // space
                 new_point_y + y);
        last_point_x = new_point_x;
        last_point_y = new_point_y;
    }

}

int main(void){

    //using a rotation of M_PI to ensure the shape is the correct way up
    drawRegularNGon(150,150,100,7, M_PI); 
    return 0;
}
