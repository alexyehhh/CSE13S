#include "heap.h"

#include "stats.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first; //left child
    uint32_t right = left + 1; //right child
    if (right <= last
        && cmp(stats, A[right - 1], A[left - 1])
               > 0) { //if right <= last and A[right - 1] > A[left - 1]
        return right; //return right child
    }
    return left; //return left child
}

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false; //set found to false
    uint32_t mother = first; //set mother to first
    uint32_t great = max_child(stats, A, mother, last); //set great to max child
    while (mother <= last / 2 && !found) { //while mother <= last / 2 and not found
        if (cmp(stats, A[mother - 1], A[great - 1]) < 0) { //if A[mother - 1] < A[great - 1]
            swap(stats, &A[mother - 1], &A[great - 1]); //swap A[mother - 1] and A[great - 1]
            mother = great; //set mother to great
            great = max_child(stats, A, mother, last); //set great to max child
        } else {
            found = true; //set found to true
        }
    }
}

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = last / 2; father > first - 1; father--) {
        fix_heap(stats, A, father, last); //fix heap
    }
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1; //set first to 1
    uint32_t last = n; //set last to n which is the length of the array
    build_heap(stats, A, first, last); //build heap
    for (uint32_t leaf = last; leaf >= first; leaf--) {
        swap(stats, &A[first - 1], &A[leaf - 1]); //swap A[first - 1] and A[leaf - 1]
        fix_heap(stats, A, first, leaf - 1); //fix heap
    }
}
