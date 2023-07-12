#include "mathlib.h"

#include <stdio.h>

static int computed_terms = 0; //static variable to keep track of computed terms

//approximate the value of pi using the Bailey-Borwein-Plouffe formula
double pi_bbp(void) {
    computed_terms = 0; //initialize computed terms variable to 0
    double sum = 0.0; //start sum at 0
    double term = 1.0; //set term to 1 because for loop won't run if term starts at 0
    double multiplier = 1.0; //set multiplier to 1 because 16^0 = 1
    for (double k = 0; absolute(term) > EPSILON; k++) {
        term = (4.0 / (8.0 * k + 1.0)) - (2.0 / (8.0 * k + 4.0)) - (1.0 / (8.0 * k + 5.0))
               - (1.0 / (8.0 * k + 6.0)); //compute next term and multiply by the previous term
        term *= multiplier; //multiply the term by the multiplier
        multiplier /= 16.0; //divide the multiplier by 16
        sum += term; //add term to the sum
        computed_terms++; //increment computed terms variable by 1
    }
    return sum; //return the sum
}

int pi_bbp_terms(void) {
    return computed_terms; //return the number of computed terms
}
