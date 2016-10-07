#include <string.h>

#include "graphics.h"

/*
 * Author: Amartya Vadlamani
 * Notes: The DSL does not support multiline strings very well. i.e. strings in
 *        the form "asdfasdfsdf \n asfasdfasfasd". This means that I need a string
 *        array to print out multiple lines
 */

void drawStrings(char **lines, int lineHeight, int x, int y){
    int index = 0;
    while (strlen(lines[index]) != 0){
        /*
         * The only string with length 0 is "", which is the terminator for my
         * array
         */
        drawString(lines[index], y, x + (index * lineHeight));
        index ++;
    }
}

int main(void){
    char *addr [6] = {"Computer Science Department,","University College London,","Gower Street,","London,","WC1E 6BT", ""};
    drawStrings(addr, 20, 20, 20);
}
