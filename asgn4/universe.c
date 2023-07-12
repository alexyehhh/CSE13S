#include "universe.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//struct definition for Universe
struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *u = malloc(sizeof(Universe)); //allocate memory for the universe
    u->rows = rows; //initialize the rows of the universe
    u->cols = cols; //initlalize the columns of the universe
    u->toroidal = toroidal; //initialize the toroidal boolean of the universe
    u->grid = (bool **) malloc(rows * sizeof(bool *)); //allocate memory for the grid
    for (uint32_t r = 0; r < rows; r++) {
        u->grid[r] = (bool *) calloc(cols, sizeof(bool)); //allocate memory for each row of the grid
    }
    return u;
}

void uv_delete(Universe *u) {
    for (uint32_t r = 0; r < u->rows; r++) {
        free(u->grid[r]); //free memory allocated for each row of the grid
        u->grid[r] = NULL; //set the row to NULL
    }
    free(u->grid); //free memory allocated for the grid
    u->grid = NULL; //set the grid to NULL
    free(u); //free memory allocated for the universe
    u = NULL; //set the universe to NULL
}

uint32_t uv_rows(Universe *u) {
    return u->rows; //return the number of rows in the universe
}

uint32_t uv_cols(Universe *u) {
    return u->cols; //return the number of columns in the universe
}

//helper function to determine if a cell is out of bounds
static bool out_of_bounds(Universe *u, uint32_t r, uint32_t c) {
    //if the row or column is greater than or equal to the number of rows or columns respectively
    if (r >= u->rows || c >= u->cols) { //>= because the rows and columns start at index 0
        return true;
    }
    return false;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    //if row and column are out of bounds, nothing changes
    if (out_of_bounds(u, r, c)) {
        return;
    }
    u->grid[r][c] = true; //set the cell at the row and coordinate to live
}

void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    //if row and column are out of bounds, nothing changes
    if (out_of_bounds(u, r, c)) {
        return;
    }
    u->grid[r][c] = false; //set the cell at the row and coordinate to dead
}

bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    //if row and column are out of bounds, return false
    if (out_of_bounds(u, r, c)) {
        return false;
    }
    return u->grid[r][c]; //return the cell at the row and column
}

//Lev(tutor) helped me with this function
bool uv_populate(Universe *u, FILE *infile) {
    uint32_t r, c; //initialize the row and column variables
    //use format specifier SCNu32 to read in unsigned 32-bit integers
    while (fscanf(infile, "%" SCNu32 " %" SCNu32 "\n", &r, &c) != EOF) {
        //if the row and column are out of bounds, return false
        if (out_of_bounds(u, r, c)) {
            return false;
        }
        uv_live_cell(u, r, c); //set the cell to live
    }
    return true; //return true if the universe is successfully populated
}

//Lev(tutor) helped me with this functions
uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    uint32_t live_neighbors = 0; //initialize the count of live_neighbors to 0
    for (int32_t x = -1; x < 2; x++) { //loop through the rows of adjacent cells
        for (int32_t y = -1; y < 2; y++) { //loop through the columns of adjacent cells
            if (x == 0 && y == 0) { //if the cell is the cell itself, continue
                continue;
            }
            uint32_t row = r + x; //add the row to the row
            uint32_t col = c + y; //add the column to the column
            if (u->toroidal) {
                row += u->rows; //add the number of rows to the row
                row %= u->rows; //mod the row by the number of rows
                col += u->cols; //add the number of columns to the column
                col %= u->cols; //mod the column by the number of columns
            } else if (out_of_bounds(
                           u, row, col)) { //if the row and column are out of bounds, continue
                continue;
            }
            live_neighbors
                += uv_get_cell(u, row, col); //add the cell to the count of live neighbors
        }
    }
    return live_neighbors; //return the number of live neighbors
}

void uv_print(Universe *u, FILE *outfile) {
    for (uint32_t r = 0; r < u->rows; r++) { //loop through the rows of the universe
        for (uint32_t c = 0; c < u->cols; c++) { //loop through the columns of the universe
            if (u->grid[r][c]) { //if the cell is live
                fprintf(outfile, "o"); //print 'o'
            } else {
                fprintf(outfile, "."); //if the cell is dead, print '.'
            }
        }
        fprintf(outfile, "\n"); //print new line at the end of column
    }
}
