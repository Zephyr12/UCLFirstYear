#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "graphics.h"

typedef struct cmplx{
    double x;
    double i;
} cmplx;

cmplx* new_cmplx(double x, double y){
    cmplx* z = malloc(sizeof(cmplx));
    z->x = x;
    z->i = y;
    return z;
}

cmplx* cmplx_add(cmplx* a, cmplx* b){
    cmplx* ret = malloc(sizeof(cmplx));
    ret->x = a->x + b->x;
    ret->i = a->i + b->i;
    return ret;
}

cmplx* cmplx_sqr(cmplx* a){
    cmplx* ret = malloc(sizeof(cmplx));
    ret->x = (a->x * a->x) - (a->i * a->i);
    ret->i = 2 * a->x * a->i;
    return ret;
}

double cmplx_mag(cmplx* a){
    return sqrt(a->x * a->x + a->i * a->i);
}

int getMandelbrotIterationCount(int max, double x, double i){
    cmplx* z = new_cmplx(0, 0);
    cmplx* c = new_cmplx(x, i);
    int iter = 0;
    for (iter; iter < max; iter ++){
        z = cmplx_add(cmplx_sqr(z), c);
        if (cmplx_mag(z) > 2){
            break;
        }
    }
    return iter;
}

int getValueColor(int iter){
    colour colors[7] = {
                        black,
                        blue,
                        cyan,
                        green,
                        yellow,
                        orange,
                        red,
                      };
    return colors[iter%7];
}

void drawMandelbrotPixel(int x, int y){
    double startx = -3;
    double starty = -1.2;
    double inc = 0.008;
    double xcoord = (x * inc) + startx;
    double ycoord = (y * inc) + starty;
    setColour(getValueColor(getMandelbrotIterationCount(1000, xcoord, ycoord)));
    drawRect(x,y,x+1,y+1);
}

int main(void){
    for (int x = 0; x < 500; x++){
        for (int y = 0; y < 300; y++){
            drawMandelbrotPixel(x, y);
        }
    }
}
