#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float F (float x);
double trapezoid(float a, float b, int n);

float F (float x) {
    return sin(x);
}

double trapezoid(float a, float b, int n) {
    int i;
    float h, sum, x;

    h = (b - a)/n;
    sum = 0.5 * (F(a) + F(b));
    for (i = 1 ; i < n ; i++) {
        x = a + i * h;
        sum += F(x);
    }
    sum = sum * h;
    return sum;
}

int main (void) {

    int n1 = 2, n2 = 4, p = 2;
    double a = 0, b = M_PI;
    double integral1, integral2, integral;

    integral1 = trapezoid(a, b, n1);
    printf("%f\n", integral1);
    integral2 = trapezoid(a, b, n2);
    printf("%f\n", integral2);
    integral = integral2 + (pow(n1, p) * (integral2 - integral1))/(pow(n2, p) - pow(n1, p));
    printf("%f", integral);
    return 0;
}
