#include <stdio.h>
#include <gmp.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "numtheory.h"
#include "randstate.h"

void gcd(mpz_t g, const mpz_t a, const mpz_t b) {
    mpz_t t, temp_a, temp_b; //define variables
    mpz_init_set(temp_a, a); //set temp_a to a
    mpz_init_set(temp_b, b); //set temp_b to b
    mpz_init(t); //initialize t
    while (mpz_cmp_ui(temp_b, 0) != 0) { //while temp_b is not greater than 0
        mpz_set(t, temp_b); //set t to temp_b
        mpz_mod(temp_b, temp_a, temp_b); // b = a mod(b)
        mpz_set(temp_a, t); //set temp_a to t
    }
    mpz_set(g, temp_a); //set output g to temp_a
    mpz_clears(t, temp_a, temp_b, NULL); //clear variables
}

void mod_inverse(mpz_t o, const mpz_t a, const mpz_t n) {
    mpz_t r, newr, t, newt, q, temp, temp2; //define variables
    //newr = r' and newt = t'
    mpz_init_set(r, n); //set r to n (line 1 of pseudocode)
    mpz_init_set(newr, a); //set newr to a (line 1 of pseudocode)
    mpz_init_set_ui(t, 0); //set t to 0 (line 2 of pseudocode)
    mpz_init_set_ui(newt, 1); //set newt to 1 (line 2 of pseudoeocde)
    mpz_inits(q, temp, temp2, NULL); //initialize variables
    while (mpz_cmp_ui(newr, 0) != 0) { //while newr is not equal to 0
        mpz_fdiv_q(q, r, newr); //q = r/newr (line 4 of pseudocode)
            //line 5 step 1
        mpz_set(temp, newr); //set temp to r'
        mpz_mul(temp2, newr, q); //set temp2 to q*r'
        mpz_sub(newr, r, temp2); //set newr to r-q*r'
        mpz_set(r, temp); //set r to r'
        //mpz_set(newr, temp); //set r' to r-q*r'
        //line 6 step 1
        mpz_set(temp, newt); //set temp to t'
        mpz_mul(temp2, newt, q); //set temp2 to q*t'
        mpz_sub(newt, t, temp2); //set newt to t-q*t'
        mpz_set(t, temp); //set t to temp
        //mpz_set(newt, temp); //set t' to t-q*t'
    }
    if (mpz_cmp_ui(r, 1) > 0) { //if r is greater than 1
        mpz_set_ui(o, 0); //set output o to 0
        mpz_clears(t, newt, r, newr, q, temp, temp2, NULL);
        return;
    }
    if (mpz_cmp_ui(t, 0) < 0) { //if t is less than 0
        mpz_add(t, t, n); //t = t+n
    }
    mpz_set(o, t); //set output o to t
    mpz_clears(t, newt, r, newr, q, temp, temp2, NULL); //clear variables
}

void pow_mod(mpz_t o, const mpz_t a, const mpz_t d, const mpz_t n) {
    mpz_t v, p, temp_d, temp_p; //Define variables v, p, temp_d, and temp_p
    mpz_init_set_ui(v, 1); //set v to 1
    mpz_init_set(p, a); //set p to a
    mpz_init_set(temp_d, d); //set temp_d to d
    mpz_init(temp_p);
    while (mpz_cmp_ui(temp_d, 0) > 0) { //while temp_d is greater than 0
        if (mpz_odd_p(temp_d)) { //if temp_d is odd
            mpz_mul(v, v, p); //v = v*p
            mpz_mod(v, v, n); //v = (v*p) mod(n)
        }
        mpz_set(temp_p, p); //set temp_p to p
        mpz_mul(p, temp_p, temp_p); //p = temp_p*temp_p
        mpz_mod(p, p, n); //p = (p*p) mod(n)
        mpz_fdiv_q_ui(temp_d, temp_d, 2); //temp_d = temp_d/2
    }
    mpz_set(o, v); //set output o to v
    mpz_clears(v, p, temp_d, temp_p, NULL); //clear variables
}

//lev(tutor) helped me with this function
static void find_s_and_r(mpz_t s, mpz_t r, mpz_t n) {
    mpz_t temp_n, temp_n2; //define variables
    mpz_inits(temp_n, temp_n2, NULL); //initialize mpz_t variables
    //mpz_set_ui(temp_n2, 2); //set temp_n2 to 2
    mpz_set(temp_n, n); //set temp_n to n
    mpz_mod_ui(temp_n2, temp_n, 2); //set temp_n2 to temp_n mod 2
    while (mpz_cmp_ui(temp_n2, 0) == 0) { //while temp_n is equal to 0
        mpz_add_ui(s, s, 1); //s = s+1
        mpz_fdiv_q_ui(temp_n, temp_n, 2); //temp_n = temp_n/2
        mpz_mod_ui(temp_n2, temp_n, 2); //temp_n = temp_n mod(2)
    }
    mpz_set(r, temp_n); //set r to temp_n
    mpz_clears(temp_n, temp_n2, NULL); //clear variables
}

bool is_prime(const mpz_t n, uint64_t iters) {
    if (mpz_cmp_ui(n, 0) == 0) { //if n is equal to 0
        return 0; //return 0
    }
    if (mpz_cmp_ui(n, 1) == 0) { //if n is equal to 1
        return 0; //return 0
    }
    if (mpz_cmp_ui(n, 2) == 0) { //if n is equal to 2
        return 1; //return 1
    }
    if (mpz_cmp_ui(n, 3) == 0) {
        return 1; //return 1
    }
    //if even number return 0
    mpz_t n_1, r, s, y, j, a, two, o, value, s_1; //define variables
    mpz_inits(n_1, r, s, a, y, j, two, o, value, s_1, NULL); //initialize variables
    mpz_set_ui(value, 2); //set value to 2
    mpz_sub_ui(n_1, n, 1); //n_1 = n-1
    mpz_set_ui(s, 0); //set s to 0
    mpz_set_ui(r, 1); //set r to 1
    find_s_and_r(s, r, n_1); //find s and r (first line of pseudocode)
    mpz_sub_ui(s_1, s, 1); //s_1 = s-1
    for (uint64_t i = 1; i <= iters; i++) {
        mpz_sub_ui(two, n, 3); //two = n-3
        mpz_urandomm(a, state, two); //a = random number between 0 and n-3
        mpz_add_ui(a, a, 2); //a = a+2
        pow_mod(o, a, r, n); //o = a^r mod(n)
        mpz_set(y, o); //set y to o
        if (mpz_cmp_ui(y, 1) != 0
            && mpz_cmp(y, n_1) != 0) { //if y is not equal to 1 and y is not equal to n-1
            mpz_set_ui(j, 1); //set j to 1
            while (mpz_cmp(j, s_1) <= 0
                   && mpz_cmp(y, n_1) != 0) { //while j is less than s-1 and y is not equal to n-1
                pow_mod(o, y, value, n); //o = y^2 mod(n)
                mpz_set(y, o); //set y to o
                if (mpz_cmp_ui(y, 1) == 0) { //if y is equal to 1
                    mpz_clears(n_1, r, s, y, j, a, two, o, value, NULL); //clear variables
                    return 0; //return 0 which returns false
                }
                mpz_add_ui(j, j, 1); //set j to j+1
            }
            if (mpz_cmp(y, n_1) != 0) { //if y is not equal to n-1
                mpz_clears(n_1, r, s, y, j, a, two, o, value, s_1, NULL); //clear variables
                return 0; //return 0 which returns false
            }
        }
    }
    mpz_clears(n_1, r, s, y, j, a, two, o, value, s_1, NULL); //clear variables
    return 1; //return 1 which returns true
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    do {
        mpz_urandomb(p, state, bits); //p = random number between 0 and 2^bits
        mpz_setbit(p, bits); //set p to bits number of bits
    } while (!is_prime(p, iters)); //while p is not prime
}
