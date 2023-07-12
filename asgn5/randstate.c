#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "randstate.h"

gmp_randstate_t state;

void randstate_init(uint64_t seed) {
    gmp_randinit_mt(state); //initializs the global random state with a Mersenne Twister algorithm
    gmp_randseed_ui(state, seed); //seed the random state with the seed
    srandom(seed); //get random seed
}

void randstate_clear(void) {
    gmp_randclear(state); //clear and free all memory used by the random state
}
