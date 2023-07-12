#include "mathlib.h"

#include <math.h>
#include <stdio.h>

static int computed_terms = 0; //static variable to keep track of computed terms

//approximate the value of pi using the Madhava series
double pi_madhava(void) {
    computed_terms = 0; //initialize computed terms variable to 0
    double sum = 0.0; //start sum at 0
    double term = 1.0; //set term to 1 because first term is 1
    double numerator = 1.0; //set numerator to 1 because the first term's numerator is 1
    double denominator = 1.0; //set denominator to 1 because the first term's denominator is 1
    for (double k = 0.0; absolute(term) > EPSILON; k++) {
        term = numerator / denominator; //compute next term using numerator divided by denominator
        sum += term; //add term to the total sum
        numerator *= -1.0 / 3.0; //multiply numerator by -1/3
        denominator += 2.0; //add 2 to denominator

        computed_terms++; //increment computed terms variable by 1
    }
    sum *= sqrt_newton(12); //multiply the sum by the square root of 12
    return sum; //return the sum
}

int pi_madhava_terms(void) {
    return computed_terms; //return the number of computed terms
}
