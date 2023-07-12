#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "randstate.h"
#include "numtheory.h"
#include "ss.h"

void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters) {
    mpz_t q_1, q_1_mod_p, p_1, p_1_mod_q, two_p; //define variables
    mpz_inits(q_1, q_1_mod_p, p_1, p_1_mod_q, two_p, NULL); //initialize variables
    do {
        uint64_t end_range = (2 * nbits) / 5; //define end range
        uint64_t pbits = random() % (end_range - (nbits / 5))
                         + nbits / 5; //bits in p in range from nbits/5 to end_range
        uint64_t qbits = nbits - 2 * pbits; //set qbits to the remaining bits
        make_prime(p, pbits, iters); //create prime p
        make_prime(q, qbits, iters); //create prime q
        mpz_sub_ui(q_1, q, 1); //q_1 = q-1
        mpz_mod(q_1_mod_p, q_1, p); //q_1_mod_p = (q-1) mod p
        mpz_sub_ui(p_1, p, 1); //p_1 = p-1
        mpz_mod(p_1_mod_q, p_1, q); //p_1_mod_q = (p-1) mod q
        //need to check if (q-1) mod p is not equal to 0 and if (p-1) mod q is not equal to 0
        //if equal to 0 generate new primes
    } while (mpz_cmp_ui(q_1_mod_p, 0) == 0 || mpz_cmp_ui(p_1_mod_q, 0) == 0);
    mpz_mul(two_p, p, p); //set two_p to p*p
    mpz_mul(n, two_p, q); //n = p*p*q
    mpz_clears(q_1, q_1_mod_p, p_1, p_1_mod_q, two_p, NULL); //clear variables
}

void ss_make_priv(mpz_t d, mpz_t pq, const mpz_t p, const mpz_t q) {
    mpz_t p_1, q_1, pq_1, temp, lambda_pq, two_p, n; //define variables
    mpz_inits(p_1, q_1, pq_1, temp, lambda_pq, two_p, n, NULL); //initialize variables
    mpz_sub_ui(p_1, p, 1); //p_1 = p-1
    mpz_sub_ui(q_1, q, 1); //q_1 = q-1
    mpz_mul(pq_1, p_1, q_1); //pq_1 = (p-1)(q-1)
    mpz_mul(pq, p, q); //pq = p*q
    gcd(temp, p_1, q_1); //temp = gcd(p-1, q-1)
    mpz_fdiv_q(lambda_pq, pq_1, temp); //lambda_n = ((p-1)(q-1))/gcd(p-1, q-1)
    mpz_mul(two_p, p, p); //set two_p to p*p
    mpz_mul(n, two_p, q); //n = p*p*q
    mod_inverse(d, n, lambda_pq); //inverse of n modulo lambda(pq)
    mpz_clears(p_1, q_1, pq_1, temp, lambda_pq, two_p, n, NULL); //clear variables
}

void ss_write_pub(const mpz_t n, const char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n%s\n", n, username); //write public key to pbfile
    //%Zx is the format specifier for a hexstring
}

void ss_write_priv(const mpz_t pq, const mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n%Zx\n", pq, d); //write private key to pvfile
    //%Zx is the format specifier for a hexstring
}

void ss_read_pub(mpz_t n, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n%s\n", n, username); //read public key from pbfile
    //%Zx is the format specifier for a hexstring
}

void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n%Zx\n", pq, d); //read private key from pvfile
    //%Zx is the format specifier for a hexstring
}

void ss_encrypt(mpz_t c, const mpz_t m, const mpz_t n) {
    pow_mod(c, m, n, n); //c = m^n mod n
}

void ss_encrypt_file(FILE *infile, FILE *outfile, const mpz_t n) {
    mpz_t m, c, sqrt_n; //define variables (m for message, c for code)
    mpz_inits(m, c, sqrt_n, NULL); //initialize variables
    //(log2(sqrt(n))-1)/8
    mpz_sqrt(sqrt_n, n); //sqrt_n = sqrt(n)
    uint64_t k = (mpz_sizeinbase(sqrt_n, 2) - 1) / 8; //set k to the number of bytes in the message
    uint8_t *kbytes = malloc(k * sizeof(uint8_t)); //allocate memory for k bytes
    kbytes[0] = 0xFF; //set the zeroth byte to 0xFF
    while (!feof(infile)) { //while not at the end of the file
        size_t j = fread(kbytes + 1, sizeof(uint8_t), k - 1, infile); //read k-1 bytes from infile
        if (j == 0) { //if j is 0 then we have reached the end of the file
            break; //break out of the loop
        }
        mpz_import(m, j + 1, 1, sizeof(uint8_t), 1, 0, kbytes); //import k bytes into m
        ss_encrypt(c, m, n); //encrypt m
        gmp_fprintf(outfile, "%Zx\n", c); //write m to outfile
    }
    mpz_clears(m, c, sqrt_n, NULL); //clear variables
    free(kbytes); //free memory of block containing allocated bytes
}

void ss_decrypt(mpz_t m, const mpz_t c, const mpz_t d, const mpz_t pq) {
    pow_mod(m, c, d, pq); //m = c^d mod pq
}

void ss_decrypt_file(FILE *infile, FILE *outfile, const mpz_t d, const mpz_t pq) {
    uint64_t k = (mpz_sizeinbase(pq, 2) - 1) / 8;
    uint8_t *kbytes = malloc(k * sizeof(uint8_t));
    //iterating over lines in infile
    mpz_t m, c; //define variables (m for message, c for code)
    mpz_inits(m, c, NULL); //initialize variables
    size_t j; //initialize j
    while (!feof(infile)) {
        //scan in a hexstring, saving the hexstring as c
        int x = gmp_fscanf(infile, "%Zx\n", c); //read c from infile
        if (x == 0) { //if x is 0 then we have reached the end of the file
            break; //break out of the loop
        }
        ss_decrypt(m, c, d, pq); //decrypt c
        mpz_export(kbytes, &j, 1, sizeof(uint8_t), 1, 0,
            m); //convert m back into bytes, storing in allocated block
        fwrite(kbytes + 1, sizeof(uint8_t), j - 1, outfile); //write bytes to outfile
    }
    mpz_clears(m, c, NULL); //clear variables
    free(kbytes); //free memory of block containing allocated bytes
}
