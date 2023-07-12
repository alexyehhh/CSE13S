#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int computed_terms = 0; //static variable to keep track of computed terms

//approximate the square root of x using Newton's method
double sqrt_newton(double x) {
    double z = 0.0; //set z to 0
    double y = 1.0; //set y to 1
    computed_terms = 0; //initialize computed terms variable to 0
    while (absolute(y - z) > EPSILON) {
        z = y; //set z to y
        y = 0.5 * (z + x / z); //compute square root of x
        computed_terms++; //increment computed terms variable by 1
    }
    return y; //return the square root of x
}

int sqrt_newton_iters(void) {
    return computed_terms;
}
