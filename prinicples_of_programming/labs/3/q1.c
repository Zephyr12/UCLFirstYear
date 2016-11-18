#include<stdio.h>
#include<stdbool.h>
#include<math.h>



bool is_valid_tri(double a, double b, double c){
    return (a+b) > c && (a+c) > b && (b+c) > c;
}

double perimeter(double a, double b, double c){
    return a + b + c;
}

double semi_perimeter(double a, double b, double c){
    return 0.5 * perimeter(a,b,c);
}

double area(double a, double b, double c){
    double s = semi_perimeter(a,b,c);
    return sqrt(
            s*(s-a)*(s-b)*(s-c));
}

int main(int argc, char* argv[]){
    double a,b,c;
    scanf("%lf %lf %lf", &a, &b, &c);
    printf("%lf %lf %lf\n", a, b, c);
    if (!is_valid_tri(a,b,c)){
        fprintf(stderr, "Your triangle is invalid\n");
        return 1;
    }
    printf("perimeter: %lf\narea: %lf\n", perimeter(a,b,c), area(a,b,c));
}
