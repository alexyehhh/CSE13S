#include <stdio.h>
#include <gmp.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#include "numtheory.h"
#include "ss.h"
#include "randstate.h"

#define OPTIONS "i:o:n:vh"

static void program_usage(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "   Decrypts data using SS decryption.\n"
                    "   Encrypted data is encrypted by the encrypt program.\n\n"
                    "USAGE\n"
                    "   ./decrypt [OPTIONS]\n\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -i infile       Input file of data to decrypt (default: stdin).\n"
                    "   -o outfile      Output file for decrypted data (default: stdout).\n"
                    "   -n pvfile       Private key file (default: ss.priv).\n");
}

int main(int argc, char **argv) {
    mpz_t pq, d; //define pq and d
    mpz_inits(pq, d, NULL); //initialize pq and d
    FILE *infile = stdin; //set default input file to decrypt to stdin
    FILE *outfile = stdout; //set default output file to decrypt to stdout
    char *pvfile_name = "ss.priv"; //set default private key file name
    bool verbose = false; //set default verbose to false
    int opt = 0; //set default option to 0
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = fopen(optarg, "r"); //get input file name from user input
            break;
        case 'o':
            outfile = fopen(optarg, "w"); //get output file name from user input
            break;
        case 'n':
            pvfile_name = optarg; //get public key file name from user input
            break;
        case 'v':
            verbose = true; //set verbose to true
            break;
        case 'h':
            program_usage(); //display program usage
            return 0;
        default:
            program_usage(); //display program usage
            return 1;
        }
    }
    FILE *pvfile = fopen(pvfile_name, "r"); //open private key file
    if (pvfile == NULL) { //if private key file does not exist
        perror(pvfile_name); //print error message
        return 1;
    }
    if (infile == NULL) { //if input file does not exist
        perror(NULL); //print error message
        return 1;
    }
    ss_read_priv(pq, d, pvfile); //read private key file
    if (verbose == true) { //if verbose is true
        gmp_fprintf(stderr, "pq (%zu bits) = %Zd\n", mpz_sizeinbase(pq, 2),
            pq); //print the private modulus pq
        gmp_fprintf(
            stderr, "d  (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d); //print the private key d
    }
    ss_decrypt_file(infile, outfile, d, pq); //decrypt file
    fclose(pvfile); //close private key file
    fclose(infile); //close input file
    fclose(outfile); //close output file
    mpz_clears(pq, d, NULL); //clear mpz_t variables
    return 0; //return 0 to indicate successful execution
}
