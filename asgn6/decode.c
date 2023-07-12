#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "code.h"
#include "endian.h"
#include "io.h"
#include "trie.h"
#include "word.h"

#define OPTIONS "vi:o:h"

static void program_usage(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "   Decompresses files with the LZ78 decompression algorithm.\n"
                    "   Used with files compressed with the corresponding encoder.\n\n"
                    "USAGE\n"
                    "   ./decode [-vh] [-i input] [-o output]\n\n"
                    "OPTIONS\n"
                    "   -v          Display decompression statistics\n"
                    "   -i input    Specify input to decompress (stdin by default)\n"
                    "   -o output   Specify output of decompressed input (stdout by default)\n"
                    "   -h          Display program usage\n");
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

int main(int argc, char **argv) {
    int opt = 0; //set default option to 0
    int infile = STDIN_FILENO; //set default input file to encrypt to stdin
    int outfile = STDOUT_FILENO; //set default output file to encrypt to stdout
    bool verbose = false; //set verbose to false
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'v':
            verbose = true; //set verbose to true to print compression statistics
            break;
        case 'i':
            infile = open(optarg, O_RDONLY); //get input file name from user input
            if (infile == -1) { //if input file is not found
                fprintf(stderr, "Failed to open %s.\n", optarg); //print error message
                return 1; //exit program
            }
            break;
        case 'o':
            outfile = open(
                optarg, O_WRONLY | O_CREAT | O_TRUNC); //open output file name from user input
            //this if statement checks if the output file is in a directory that we can't access
            if (outfile == -1) { //if output file is not found
                fprintf(stderr, "Failed to open %s.\n", optarg); //print error message
                return 1; //exit program
            }
            break;
        case 'h':
            program_usage(); //display program usage
            return 0;
        default:
            program_usage(); //display program usage
            return 1;
        }
    }
    FileHeader header; //initialize header
    read_header(infile, &header); //read header from input file
    fchmod(outfile, header.protection); //set output file permissions to input file permissions
    WordTable *table = wt_create(); //create word table
    uint8_t curr_sym = 0; //initialize curr_sym to 0
    uint16_t curr_code = 0; //initialize curr_code to 0
    int next_code = START_CODE; //initialize next_code to START_CODE
    while (
        read_pair(infile, &curr_code, &curr_sym, bit_length(next_code))) { //while read_pair is true
        table[next_code]
            = word_append_sym(table[curr_code], curr_sym); //append curr_sym to table[curr_code]
        write_word(outfile, table[next_code]); //write table[next_code] to output file
        next_code = next_code + 1; //increment next_code by 1
        //if next_code is MAX_CODE
        if (next_code == MAX_CODE) {
            wt_reset(table); //reset table
            next_code = START_CODE; //set next_code to START_CODE
        }
    }
    flush_words(outfile); //flush words
    //if verbose is true
    if (verbose == true) {
        fprintf(stderr, "Compressed file size: %lu bytes\n",
            total_syms); //print compression statistics using total_syms
        fprintf(stderr, "Decompressed file size: %lu bytes\n",
            total_bits); //print compression statistics using total_bits
        fprintf(stderr, "Space saving: %3.2f%%\n",
            (100 * (1 - ((double) total_syms / total_bits)))); //print space saving
    }
    wt_delete(table); //delete table
    close(infile); //close infile
    close(outfile); //close outfile
    return 0; //return 0 to indicate successful execution of the program
}
