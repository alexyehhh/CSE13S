#include "universe.h"

#include <inttypes.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "tsn:i:o:h"

//static function to print program usage
static void program_usage(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "    Conway's Game of Life\n\n"
                    "USAGE\n"
                    "    ./life tsn:i:o:h\n\n"
                    "OPTIONS\n"
                    "    -t                 Create your universe as a toroidal\n"
                    "    -s                 Silent - do not use animate the evolution\n"
                    "    -n {number}        Number of generations [default: 100]\n"
                    "    -i {file}          Input file [default: stdin]\n"
                    "    -o {file}          Output file [default: stdout]\n");
}

int main(int argc, char **argv) {
    uint32_t generations = 100; //set default number of generations to 100
    FILE *input = stdin; //set default input as stdin
    FILE *output = stdout; //set default output as stdin
    int opt = 0; //Initialize opt equal to 0
    uint32_t rows = 0; //Initialize rows to 0
    uint32_t columns = 0; //Initialize columns to 0
    bool toroidal = false; //set toroidal default to false
    bool ncurses = true; //set ncurses default to true
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't':
            toroidal = true; //set toroidal to true
            break;
        case 's':
            ncurses = false; //silence ncurses
            break;
        case 'n': {
            int32_t generations
                = strtoul(optarg, NULL, 10); //set number of generations to user input
            //turn uint32_t into signed int64_t to check if it is negative
            if (generations < 0) { //if number of generations is negative
                fprintf(
                    stderr, "Error: Number of generations must be greater than or equal to 0\n");
                return 1;
            }
        }
            //turn generations back into a uint32_t
            generations = (uint32_t) generations;
            break;
        case 'i':
            input = fopen(optarg, "r"); //set input to user input
            //if input file does not exist
            if (input == NULL) {
                fprintf(stderr, "Error opening %s.\n", optarg);
                return 1;
            }
            break;
        case 'o':
            output = fopen(optarg, "w"); //set output to user input
            break;
        case 'h':
            program_usage(); //print usage
            return 1;
        default:
            program_usage(); //print usage
            return 1;
        }
    }

    //Use fscanf to read the number of rows and columns of the universe you will be populating from the specified input
    //use format specifier SCNu32 to read in the number of rows and columns
    if (fscanf(input, "%" SCNu32 " %" SCNu32 "\n", &rows, &columns) != 2) {
        fprintf(stderr, "Malformed input.\n");
        return 1;
    }
    //create two universes using the dimensions obtained using fscanf
    //Mark universes as toroidal if -t was specified
    Universe *A = uv_create(rows, columns, toroidal); //create universe A
    Universe *B = uv_create(rows, columns, toroidal); //create universe B
    //populate universe A using uv_populate with the remainder of the input
    if (uv_populate(A, input) == false) {
        uv_delete(A); //delete universe A
        uv_delete(B); //delete universe B
        fprintf(stderr, "Malformed input.\n"); //print error message
        return 1;
    }
    //setup the ncurses screen
    if (ncurses == true) {
        initscr(); //initialize the screen
        curs_set(false); //hide the cursor
    }
    //for each generation up to the number of generations specified by -n or 100
    for (uint32_t i = 0; i < generations; i++) {
        //if ncurses isn't silenced by the -s option, clear the screen, display universe A, refresh the screen, and sleep for 50000 microseconds
        if (ncurses == true) {
            clear(); //clear the window
            for (uint32_t x = 0; x < rows; x++) { //iterate through rows
                for (uint32_t y = 0; y < columns; y++) { //iterate through columns
                    if (uv_get_cell(A, x, y)) { //if cell is live
                        mvprintw(x, y, "o"); //print 'o'
                    }
                }
            }
            refresh(); //refresh the window
            usleep(50000); //sleep for 50000 microseconds
        }
        //perform one generation by taking a census of each cell in universe A and either setting or clearing the corresponding cell in universe B
        for (uint32_t j = 0; j < rows; j++) {
            for (uint32_t k = 0; k < columns; k++) {
                uint32_t count = uv_census(A, j, k); //take the census of each cell in universe A
                if (count == 3) { //if dead cell has 3 live neighbors
                    uv_live_cell(B, j, k); //mark cell as live
                } else if (count == 2 && uv_get_cell(A, j, k)) { //if live cell has 2 live neighbors
                    uv_live_cell(B, j, k); //mark cell as live
                } else {
                    uv_dead_cell(B, j, k); //mark cell as dead because all other cells die
                }
            }
        }
        //swap the universes A and B
        Universe *temp = A; //create a temporary universe
        A = B; //set A to B
        B = temp; //set B to temp
    }
    //if ncurses isn't silenced by the -s option
    if (ncurses == true) {
        endwin(); //close the screen
    }
    uv_print(A, output); //output universe A to the specified file
    //delete the universes
    uv_delete(A); //delete universe A
    uv_delete(B); //delete universe B
    //close the input and output files
    fclose(input); //close input file
    fclose(output); //close output file
    return 0; //return 0 to indicate successful execution of the program
}
