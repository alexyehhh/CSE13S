#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int computed_terms = 0; //static variable to keep track of computed terms

//approximate the value of e using Taylor Series
double e(void) {
    computed_terms = 0; //initialize computed terms variable to 0
    double sum
        = 1.0; //start sum at 1 because you can't divide 1 by 0 when calcualting the first term
    double term = 1.0; //set term to 1 because first term is 1
    for (double k = 1.0; absolute(term) > EPSILON; k++) {
        term *= 1.0 / k; //compute next term and multiply by the previous term
        sum += term; //add term to the sum
        computed_terms++; //increment computed terms variable by 1
    }
    return sum; //return the sum
}

int e_terms(void) {
    return computed_terms; //return the number of computed terms
}
