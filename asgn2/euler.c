#include "mathlib.h"

#include <stdio.h>

static int computed_terms = 0; //static variable to keep track of computed terms

//approximate the value of pi using Euler's solution to the Basel problem
double pi_euler(void) {
    computed_terms = 0; //initialize computed terms variable to 0
    double sum = 0.0; //start sum at 0
    double term = 1.0; //set term to 1 because first term is 1
    for (double k = 1.0; absolute(term) > EPSILON; k++) {
        term = (1.0 / (k * k)); //compute next term
        sum += term; //add term to the sum
        computed_terms++; //increment computed terms variable by 1
    }
    sum *= 6; //multiply the sum by 6
    sum = sqrt_newton(sum); //take the square root of the sum
    return sum; //return the sum
}

int pi_euler_terms(void) {
    return computed_terms; //return the number of computed terms
}
