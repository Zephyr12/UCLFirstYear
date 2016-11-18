#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "graphics.h"
typedef struct turtle{
    float position_x;
    float position_y;

    float degrees;
} turtle_t;

turtle_t *turtle = NULL;

float deg_to_rad(float deg){
    return (deg/180)*3.14159265;
}

void turtle_init(float x, float y, float degrees){
    turtle = malloc(sizeof(turtle));
    turtle->position_x = x;
    turtle->position_y = y;
    turtle->degrees = degrees;
}

void right (float degrees){
    turtle->degrees += degrees;
}

void left (float degrees){
    right(-degrees);
}

void forwards(float distance){
    int old_x = (int)turtle->position_x;
    int old_y = (int)turtle->position_y;
    turtle->position_x += distance * sin(deg_to_rad(turtle->degrees));
    turtle->position_y += distance * cos(deg_to_rad(turtle->degrees));
    int new_x = (int)turtle->position_x;
    int new_y = (int)turtle->position_y;
    drawLine(old_x, old_y, new_x, new_y);
}

void draw_koch_curve(int iterations, float dist){
    if (iterations <= 0){
        forwards(dist);
        return;
    }
    draw_koch_curve(iterations - 1, dist/3);
    right(60);
    draw_koch_curve(iterations - 1, dist/3);
    left(120);
    draw_koch_curve(iterations - 1, dist/3);
    right(60);
    draw_koch_curve(iterations - 1, dist/3);
}

void main(){
    turtle_init(100, 100, 90);
    draw_koch_curve(5, 200);
    left(120);
    draw_koch_curve(5, 200);
    left(120);
    draw_koch_curve(5, 200);
    left(120);
}
