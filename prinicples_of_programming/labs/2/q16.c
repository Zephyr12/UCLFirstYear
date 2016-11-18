#include "graphics.h"
#include <stdio.h>
#include <math.h>

typedef struct vec2{
    double x;
    double y;
} vec2_t;

vec2_t add(vec2_t a, vec2_t b){
    vec2_t r = {a.x + b.x, a.y + b.y};
    return r;
}

vec2_t scalar_mul(vec2_t a, double m){
    vec2_t r = {a.x * m, a.y * m};
    return r;
}

vec2_t angle_magnitude(double angle, double magnitude){
    vec2_t r = {sin(angle)*magnitude, -cos(angle)*magnitude};
    return r;
}

void draw_rect(int x, int y, int w, int h, double rot){
    vec2_t origin = {x, y};
    vec2_t up = angle_magnitude(rot, h);
    vec2_t down = angle_magnitude(rot, -h);
    vec2_t left = angle_magnitude(rot + (M_PI/2), w);
    vec2_t right = angle_magnitude(rot + (M_PI/2), -w);
    vec2_t verts[5] = {
        add(add(origin, up), right),
        add(add(origin, up), left),
        add(add(origin, down), left),
        add(add(origin, down), right),
        add(add(origin, up), right),
    };

    for (int v = 1; v < 5; v++){
        vec2_t vert_last = verts[v-1];
        vec2_t vert_current = verts[v];
        drawLine(vert_last.x, vert_last.y, vert_current.x, vert_current.y);
    }
}

void draw_triangle(int x, int y, double verts[][2], double rot){
    vec2_t origin = {x,y};

    vec2_t world_space_verts[4] = {
        add(angle_magnitude(verts[0][1]+rot, verts[0][0]), origin),
        add(angle_magnitude(verts[1][1]+rot, verts[1][0]), origin),
        add(angle_magnitude(verts[2][1]+rot, verts[2][0]), origin),
        add(angle_magnitude(verts[0][1]+rot, verts[0][0]), origin),
    };

    for (int v = 1; v < 4; v++){
        vec2_t vert_last = world_space_verts[v-1];
        vec2_t vert_current = world_space_verts[v];
        drawLine(vert_last.x, vert_last.y, vert_current.x, vert_current.y);
    }

}

int main(void){
    /*double triangle[3][2] = {
        {100.0,0.0},
        {100.0,(2.0/3.0)*M_PI},
        {100.0,(4.0/3.0)*M_PI}
    };*/
//    double **tris = (double**)&triangle;
    for (int i = 1; i <= 10; i++){
        draw_rect(i*45, i*i*5, i*4, 30, (i/10.0) * M_PI);
        draw_triangle(
                i*45,
                i*i*5, 
                (double[3][2]){
                    {10*i,0.0},
                    {100.0,(2.0/3.0)*M_PI},
                    {100.0,(4.0/3.0)*M_PI}
                },
                (i/10.0) * M_PI
                );
    }
}
