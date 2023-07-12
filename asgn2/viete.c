#include "mathlib.h"

#include <stdio.h>

static int computed_terms = 0; //static variable to keep track of computed terms

//lev(tutor) helped me with this function
//approximate the value of pi using the Viète formula
double pi_viete(void) {
    double previous = 0.0; //set previous to 0
    double current = sqrt_newton(2.0); //set current to the square root of 2
    double sum = current / 2; //set sum to the current term divided by 2
    computed_terms = 0; //initialize computed terms variable to 0
    while (absolute(current - previous) > EPSILON) {
        previous = current; //set previous to current
        current = sqrt_newton(2.0 + previous); //compute the next term
        sum *= current / 2.0; //multiply the sum by the current term
        computed_terms++; //increment computed terms variable by 1
    }
    sum = 2.0 / sum; //divide 2 by the sum
    return sum; //return the sum
}

int pi_viete_factors(void) {
    return computed_terms; //return the number of computed terms
}
