#include "shell.h"

#include "gaps.h"
#include "stats.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    //for gap in gaps:
    for (uint32_t x = 0; x < GAPS; x++) {
        uint32_t gap = gaps[x]; //set the gap to each iteration of gaps
        for (uint32_t i = gap; i < length; i++) {
            uint32_t j = i; //set j to i
            uint32_t temp = move(stats, arr[i]); //set temp to arr[i]
            while (j >= gap
                   && cmp(stats, temp, arr[j - gap]) < 0) { //while j >= gap and temp < arr[j - gap]
                arr[j] = move(stats, arr[j - gap]); //arr[j] = arr[j - gap]
                j -= gap; //subtract gap from j
            }
            arr[j] = move(stats, temp); //arr[j] = temp
        }
    }
}
