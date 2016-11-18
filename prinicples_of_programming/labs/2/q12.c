#include<math.h>
#include<stdlib.h>
#include<stdio.h>

#include "graphics.h"

typedef struct function{
    double (*fn)(double);
    colour col;
} function_t;

function_t* create_function(double (*fn)(double), colour col){
    function_t* func = malloc(sizeof(function_t));
    func->fn = fn;
    func->col = col;
    return func;
}

double evaluate_function(function_t* func, double arg){
    return -(*(func->fn))(arg);
}

typedef struct graph{
    function_t** functions;
    int num_functions;
    float x_min; 
    float x_max; 
    float y_min; 
    float y_max; // the values that the graph is plotted against
    float val_inc_x;
    float val_inc_y;

    float origin_x;
    float origin_y;
    float size_x;
    float size_y;
} graph_t;

graph_t* create_graph(
            function_t** functions,
            int num_functions,
            float x_min, 
            float x_max, 
            float y_min, 
            float y_max,
            float val_inc_x,
            float val_inc_y,
            float origin_x,
            float origin_y,
            float size_x,
            float size_y){
    graph_t* graph = malloc(sizeof(graph_t));
    graph->functions = functions;
    graph->num_functions = num_functions;
    graph->x_min = x_min;
    graph->x_max = x_max;
    graph->y_min = y_min;
    graph->y_max = y_max;
    graph->val_inc_x = val_inc_x;
    graph->val_inc_y = val_inc_y;

    graph->origin_x = origin_x;
    graph->origin_y = origin_y;
    graph->size_x = size_x;
    graph->size_y = size_y;
    return graph;
}

void draw_graph(graph_t* graph){
    setColour(white);
    drawLine(0, graph->origin_y, 500, graph->origin_y); 
    drawLine(graph->origin_x, 0, graph->origin_x, 300); //draw the axis lines
    float scale_factor_x = (graph->x_max - graph->x_min) / (graph->size_x);
    float scale_factor_y = (graph->y_max - graph->y_min) / (graph->size_y);
    for (float x_val = graph->x_min; x_val < graph->x_max; x_val += graph->val_inc_x){
        if (abs(x_val) < graph->val_inc_x){
            continue;
        }
        int x_screen_coord = graph->origin_x + (x_val / scale_factor_x);
        drawLine(x_screen_coord, graph->origin_y - 5, x_screen_coord, graph->origin_y + 5);
        char buffer[5];
        sprintf(buffer, "%5.2f", x_val);
        drawString(buffer, x_screen_coord, graph->origin_y - 10);
    }
    for (float y_val = graph->y_min; y_val < graph->y_max; y_val += graph->val_inc_y){
        int y_screen_coord = graph->origin_y + (y_val / scale_factor_y);
        drawLine( graph->origin_x - 5, y_screen_coord, graph->origin_x + 5, y_screen_coord);
        char buffer[5];
        sprintf(buffer, "%5.2f", y_val);
        drawString(buffer, graph->origin_x + 10, y_screen_coord);
    }
    for (int fn_indx = 0; fn_indx < graph->num_functions; fn_indx++){
        function_t* func = graph->functions[fn_indx];
        setColour(func->col);
        float old_y = 0;
        for (int x = 0; x < 500; x ++){
            float new_y =  evaluate_function(func, (x-250)*scale_factor_x)/scale_factor_y;
            if (!(abs(old_y - new_y) > 300)){
                drawLine(x - 1, old_y + graph->origin_y, x, new_y + graph->origin_y);
            }
            old_y = new_y;
        }
    }
}

double csc(double deg){
    return 1 / sin(deg);
}

double sec(double deg){
    return 1 / cos(deg);
}

double cot(double deg){
    return 1/tan(deg);
}

double x_square(double deg){
    return pow(deg, 2);
}

double test_8(double x){
    return x;
}

int main(void){
    setColour(black);
    fillRect(0,0,500,300);
    function_t **functions = malloc(8*sizeof(function_t*));
    functions[0] = create_function(&sin, red);
    functions[1] = create_function(&cos, blue);
    functions[2] = create_function(&tan, green);
    functions[3] = create_function(&csc, pink);
    functions[4] = create_function(&sec, cyan);
    functions[5] = create_function(&cot, orange);
    functions[6] = create_function(&x_square, white);
    functions[7] = create_function(&test_8, yellow);
    graph_t* graph = create_graph(functions, 8, -M_PI, M_PI, -4, 4, 0.5, 0.4, 250, 150, 500, 300);
    draw_graph(graph);
}
