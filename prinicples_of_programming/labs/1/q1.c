// Written by UCL CS dpt.
// Copied by Amartya Vadlamani, 4th October 2016
// This program displays my name.

#include <stdio.h>
#include <string.h>
int main(void) {
    char myName[] = "Amartya Vadlamani";
    printf("Hello, my name is %s\n", myName);

    int index = strlen(myName) - 1;

    while (index > -1){
        printf("%c", myName[index]);
        index = index - 1;
    }

    printf("\n");
    return 0;
}
