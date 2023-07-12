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
                    "   Compresses files using the LZ78 compression algorithm.\n"
                    "   Compressed files are decompressed with the corresponding decoder.\n\n"
                    "USAGE\n"
                    "   ./encode [-vh] [-i input] [-o output]\n\n"
                    "OPTIONS\n"
                    "   -v          Display compression statistics\n"
                    "   -i input    Specify input to compress (stdin by default)\n"
                    "   -o output   Specify output of compressed input (stdout by default)\n"
                    "   -h          Display program help and usage\n");
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
            infile = open(optarg, O_RDONLY); //open input file name from user input
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
    struct stat stats; //create a new struct stat
    fstat(infile, &stats); //get the stats of the input file
    FileHeader header = { 0 }; //create a new file header
    header.magic = MAGIC; //set the magic number of the header to MAGIC
    header.protection
        = stats.st_mode; //set the protection of the header to the protection of the input file
    //create a new file header using the magic number and the protection of the input file
    fchmod(outfile, header.protection); //set permissions of the output file
    write_header(outfile, &header); //write the header to the output file
    TrieNode *root = trie_create(); //Create a new trie using trie_create()
    TrieNode *curr_node = root; //set the current node to the root
    TrieNode *prev_node = NULL; //set the previous node to NULL
    uint8_t curr_sym = 0; //set the current symbol to 0
    uint8_t prev_sym = 0; //set the previous symbol to 0
    uint16_t next_code = START_CODE; //set the next code to START_CODE
    while (read_sym(infile, &curr_sym)) { //read the next symbol from the input file
        TrieNode *next_node = trie_step(curr_node,
            curr_sym); //set the next node to the trie_step of the current node and the current symbol
        //if next_node is not NULL
        if (next_node != NULL) {
            prev_node = curr_node; //set the previous node to the current node
            curr_node = next_node; //set the current node to the next node
        } else {
            write_pair(outfile, curr_node->code, curr_sym,
                bit_length(next_code)); //write the pair to the output file
            curr_node->children[curr_sym]
                = trie_node_create(next_code); //create a new trie node with the next code
            curr_node = root; //set the current node to the root
            next_code = next_code + 1; //increment the next code
        }
        //if next_code is MAX_CODE
        if (next_code == MAX_CODE) {
            trie_reset(root); //reset the trie to the root
            curr_node = root; //set the current node to the root
            next_code = START_CODE; //set the next code to START_CODE
        }
        prev_sym = curr_sym; //set the previous symbol to the current symbol
    }
    //if curr_node is not root
    if (curr_node != root) {
        write_pair(outfile, prev_node->code, prev_sym,
            bit_length(next_code)); //write the pair to the output file
        next_code = (next_code + 1) % MAX_CODE; //increment the next code
    }
    write_pair(outfile, STOP_CODE, 0, bit_length(next_code)); //write the pair to the output file
    flush_pairs(outfile); //flush the pairs to the output file
    //if -v is specified
    if (verbose == true) {
        fprintf(stderr, "Compressed file size: %lu bytes\n",
            total_bits); //print the compressed file size using total bits
        fprintf(stderr, "Decompressed file size: %lu bytes\n",
            total_syms); //print the decompressed file size using total symbols
        fprintf(stderr, "Space saving: %3.2f%%\n",
            (100 * (1 - ((double) total_bits / total_syms)))); //print the space saving
    }
    close(infile); //close infile
    close(outfile); //close outfile
    trie_delete(root); //delete trie to free memory
    return 0; //return 0 to indicate successful execution of the program
}
