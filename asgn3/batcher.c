#include "batcher.h"

#include "stats.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {
    if (cmp(stats, A[x], A[y]) > 0) { //if A[x] > A[y]
        swap(stats, &A[x], &A[y]); //swap A[x] and A[y]
    }
}

//Miles(tutor) helped me write this function.
static uint8_t bit_length(uint32_t x) {
    uint8_t t = 0; //initialize t to 0
    while (x != 0) {
        x >>= 1; //right shift x by 1
        t++; //increment t
    }
    return t;
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) { //if the length of the array is 0, return
        return;
    }
    uint32_t t = bit_length(n); //set t to the bit length of n
    uint32_t p = 1 << (t - 1); //set p to 1 shifted left by t - 1
    while (p > 0) {
        uint32_t q = 1 << (t - 1); //set q to 1 shifted left by t - 1
        uint32_t r = 0; //set r to 0
        uint32_t d = p; //set d to p
        while (d > 0) {
            for (uint32_t i = 0; i < n - d; i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d); //call comparator
                }
            }
            d = q - p; //set d to q - p
            q >>= 1; //right shift q by 1
            r = p; //set r to p
        }
        p >>= 1; //right shift p by 1
    }
}
