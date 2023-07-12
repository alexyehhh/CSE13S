#include "set.h"

Set set_empty(void) {
    return 0;
}

Set set_universal(void) {
    return ~((uint32_t) 0); //set each bit to 1
}

Set set_insert(Set s, uint8_t x) {
    return s | (1 << (x % 32)); //return s with the bit corresponding to x set to 1
}

Set set_remove(Set s, uint8_t x) {
    return s & ~(1 << (x % 32)); //return s with the bit corresponding to x cleared to 0
}

bool set_member(Set s, uint8_t x) {
    return s & (1 << (x % 32)); //return true if the given value x is in the set s
}

Set set_union(Set s, Set t) {
    return s | t; //return the union of sets s and t
}

Set set_intersect(Set s, Set t) {
    return s & t; //return the intersection of sets s and t
}

Set set_difference(Set s, Set t) {
    return s & ~t; //return the difference of sets s and t (elements of s not in t)
}

Set set_complement(Set s) {
    return ~s; //return all bits in the set that are flipped
}
