/*
 * Author: Amartya Vadlamani
 * Notes: Yay stucts and functions. That means pointers. Which means allocating
 *        memory. Which means freeing memory. Which means segfaults death and dispair
 *        for all! Fun!
 *
 *        Ok upon closer inspection the question just asked for a still image of a
 *        bar chart not a miniature plotting library! Oops
 */

#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"

typedef struct column {
    char* name;
    int width;
    int value;
} column_t;

typedef struct bar_chart {
    int y_axis_increment;
    column_t** columns;
    int column_count;
} bar_chart_t;

void drawChart(bar_chart_t* chart, int x, int y, int height){
   int max_value = 0; 
   for (int i = 0; i < chart->column_count; i++){
       column_t* col = chart->columns[i];
       if (col->value >= max_value){
           max_value = col->value;
       }
   }
   float scale_ratio = height / max_value;
   // get a conversion factor from values to pixels

   int total_width = 0;
   for (int i = 0; i < chart->column_count; i++){
       total_width += chart->columns[i]->width;
   }

   drawLine(x,y,x+total_width+chart->column_count,y);
   // draw a line for the horizontal axis 
   drawLine(x,y,x,y-height);
   // draw a line for the y axis

   int current_increment = 0;
   while(current_increment <= max_value){
       // draw the y axis' increments and labels
       current_increment += chart->y_axis_increment;
       int increment_width = 2;
       int increment_y = y - (int)(scale_ratio * current_increment);
       drawLine(x - increment_width, increment_y, x + increment_width, increment_y);
       char buffer[9];
       snprintf(buffer, 9, "%d", current_increment); // assuming values dont go over 9 digits
       drawString(buffer, x - 20, increment_y);
   }
   int current_column_offset = 1; // to stop the first column from overwriting the y axis
   for(int i = 0; i < chart->column_count; i++){
       column_t* col = chart->columns[i];
       setColour(i % 10);// trying to figure out how to get full shaded rectangles
       drawRect(x + current_column_offset, y - (int)(scale_ratio * col->value) - 1, col->width, (int)(scale_ratio * col->value));
       // the -1 is to give a space to show the x-axis line instead of drawing over it
       setColour(black);
       drawString(col->name, x+current_column_offset + 5, y + 15);
       current_column_offset += col->width + 1;
       // to stop the columns from overwriting eachother
   }
}

column_t* new_column(char* name, int width, int value){
    column_t* c = malloc(sizeof(column_t));
    c->name = name;
    c->width = width;
    c->value = value;
    return c;
}

bar_chart_t* new_bar_char(int y_axis_increment, column_t** columns, int column_count){
    bar_chart_t* chart = malloc(sizeof(bar_chart_t));
    chart->column_count = column_count;
    chart->columns = columns;
    chart->y_axis_increment = y_axis_increment;
    return chart;
}

int main(void){
    column_t* c1 = new_column("Alpha", 45, 36);
    column_t* c2 = new_column("Beta", 40, 49);
    column_t* c3 = new_column("Gamma", 55, 22);
    column_t* c4 = new_column("Delta", 55, 93);
    column_t ** cols = malloc(4*sizeof(column_t*));
    cols[0] = c1;
    cols[1] = c2;
    cols[2] = c3;
    cols[3] = c4;

    bar_chart_t* chart = new_bar_char(20, cols, 4);
    drawChart(chart, 50, 200, 100);
}
