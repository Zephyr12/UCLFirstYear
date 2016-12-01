#include <math.h> 
#include<stdio.h>
int main (void){
    double series = 0.0;

    for(double k = 0.0; k <= 100.0; k += 1){
        double term = (pow(-3.0,(0.0-k)))/(2.0*k+1.0);
        series = series+term;
    }

    printf("%f\n", series*(pow(12.0,(1.0/2.0))));
    return 0;
}
