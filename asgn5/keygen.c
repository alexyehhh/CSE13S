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

#define OPTIONS "b:i:n:d:s:vh"

static void program_usage(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "   Generates an SS public/private key pair.\n\n"
                    "USAGE\n"
                    "   ./keygen [OPTIONS]\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -b bits         Minimum bits needed for public key n (default: 256).\n"
                    "   -i iterations   Miller-Rabin iterations for testing primes (default: 50).\n"
                    "   -n pbfile       Public key file (default: ss.pub).\n"
                    "   -d pvfile       Private key file (default: ss.priv).\n"
                    "   -s seed         Random seed for testing.\n");
}

int main(int argc, char **argv) {
    uint64_t bits = 256; //set default number of bits to 256
    uint64_t iterations = 50; //set default number of iterations to 50
    char *pbfile_name = "ss.pub"; //set default public key file name
    char *pvfile_name = "ss.priv"; //set default private key file name
    uint64_t seed = time(NULL); //set default seconds since UNIX epoch
    bool verbose = false; //set default verbose to false
    int opt = 0; //set default option to 0
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b':
            bits = strtoul(optarg, NULL, 10); //get number of bits from user input
            break;
        case 'i':
            iterations = strtoul(optarg, NULL, 10); //get number of iterations from user input
            break;
        case 'n':
            pbfile_name = optarg; //get public key file name from user input
            break;
        case 'd':
            pvfile_name = optarg; //get private key file name from user input
            break;
        case 's':
            seed = strtoul(optarg, NULL, 10); //get seed from user input
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
    FILE *pbfile = fopen(pbfile_name, "w"); //open public key file
    if (pbfile == NULL) { //if the public key file doesn't exist
        perror(pbfile_name); //print error message
        return 1;
    }
    FILE *pvfile = fopen(pvfile_name, "w"); //open private key file
    if (pvfile == NULL) { //if the private key file doesn't exist
        perror(pvfile_name); //print error message
        return 1;
    }
    fchmod(fileno(pvfile), 0600); //set permissions for public key file
    randstate_init(seed); //initialize random state
    mpz_t p, q, n, d, pq; //define variables
    mpz_inits(p, q, n, d, pq, NULL); //initialize variables
    ss_make_pub(p, q, n, bits, iterations); //make public key
    ss_make_priv(d, pq, p, q); //make private key
    char *username = getenv("USER"); //get current user's name as a string
    ss_write_pub(n, username, pbfile); //write public key to public key file
    ss_write_priv(pq, d, pvfile); //write private key to private key file
    if (verbose == true) { //if verbose is true/-v was enabled
        gmp_fprintf(stderr, "user = %s\n", username); //print username
        gmp_fprintf(stderr, "p  (%zu bits) = %Zd\n", (mpz_sizeinbase(p, 2)),
            p); //print the first large prime p
        gmp_fprintf(stderr, "q  (%zu bits) = %Zd\n", (mpz_sizeinbase(q, 2)),
            q); //print the second large prime q
        gmp_fprintf(
            stderr, "n  (%zu bits) = %Zd\n", (mpz_sizeinbase(n, 2)), n); //print the public key n
        gmp_fprintf(stderr, "pq  (%zu bits) = %Zd\n", (mpz_sizeinbase(pq, 2)),
            pq); //print the private modulus pq
        gmp_fprintf(stderr, "d  (%zu bits) = %Zd\n", (mpz_sizeinbase(d, 2)),
            d); //print the private exponent d
    }
    fclose(pbfile); //close public key file
    fclose(pvfile); //close private key file
    randstate_clear(); //clear random state
    mpz_clears(p, q, n, d, pq, NULL); //clear mpz_t variables
    return 0; //return 0 to indicate successful execution
}
