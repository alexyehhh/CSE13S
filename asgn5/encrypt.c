#include <stdio.h>
#include <gmp.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>

#include "numtheory.h"
#include "ss.h"
#include "randstate.h"

#define OPTIONS "i:o:n:vh"

static void program_usage(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "   Encrypts data using SS encryption.\n"
                    "   Encrypted data is decrypted by the decrypt program.\n\n"
                    "USAGE\n"
                    "   ./encrypt [OPTIONS]\n\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -i infile       Input file of data to encrypt (default: stdin).\n"
                    "   -o outfile      Output file for encrypted data (default: stdout).\n"
                    "   -n pbfile       Public key file (default: ss.pub).\n");
}

int main(int argc, char **argv) {
    mpz_t n; //set default public key n to 0
    mpz_init(n); //initialize public key n
    char username[LOGIN_NAME_MAX]; //set default username to the maximum length of a username
    FILE *infile = stdin; //set default input file to encrypt to stdin
    FILE *outfile = stdout; //set default output file to encrypt to stdout
    char *pbfile_name = "ss.pub"; //set default public key file name
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
            pbfile_name = optarg; //get public key file name from user input
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
    FILE *pbfile = fopen(pbfile_name, "r"); //open public key file
    if (pbfile == NULL) { //if public key file does not exist
        perror(pbfile_name); //print error message
        return 1;
    }
    if (infile == NULL) { //if input file does not exist
        perror(NULL); //print error message
        return 1;
    }
    ss_read_pub(n, username, pbfile); //read public key from opened public key file
    if (verbose == true) { //if verbose is true
        gmp_fprintf(stderr, "user = %s\n", username); //print username
        gmp_fprintf(stderr, "n (%zu bits) = %Zd\n", (mpz_sizeinbase(n, 2)), n); //print public key n
    }
    ss_encrypt_file(infile, outfile, n); //encrypt file
    fclose(pbfile); //close public key file
    fclose(infile); //close input file
    fclose(outfile); //close output file
    mpz_clear(n); //clear mpz_t variable n
    return 0; //return 0 to indicate successful execution
}
