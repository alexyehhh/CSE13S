#include "word.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "io.h"
#include "endian.h"
#include "code.h"

#define BLOCK 4096 // 4KB blocks.
#define MAGIC 0xBAADBAAC // Unique encoder/decoder magic number.

uint64_t total_syms; // To count the symbols processed.
uint64_t total_bits; // To count the bits processed.

int read_bytes(int infile, uint8_t *buf, int to_read) {
    int bytes_read = 0; //number of bytes read
    int bytes = 0; //number of bytes
    while (bytes_read < to_read) {
        bytes = read(infile, buf + bytes_read, to_read - bytes_read); //read bytes from infile
        if (bytes == 0) { //if bytes is 0, break
            break;
        }
        if (bytes == -1) { //if bytes is -1, print error and exit
            fprintf(stderr, "Error reading file");
            return 1;
        }
        bytes_read += bytes; //add bytes to number of bytes read
    }
    total_syms += bytes_read; //add number of bytes read to total symbols
    return bytes_read; //return number of bytes read
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int bytes_written = 0; //number of bytes written
    int bytes = 0; //number of bytes
    while (bytes_written < to_write) {
        bytes = write(
            outfile, buf + bytes_written, to_write - bytes_written); //write bytes to outfile
        if (bytes == 0) { //if bytes is 0, break
            break;
        }
        if (bytes == -1) { //if bytes is -1, error
            fprintf(stderr, "Error writing file");
            return 1;
        }
        bytes_written += bytes; //add bytes to number of bytes written
    }
    total_bits += bytes_written; //add number of bytes written to total_bits
    return bytes_written; //return number of bytes written
}

void read_header(int infile, FileHeader *header) {
    //read bytes from infile
    int bytes_read = read_bytes(infile, (uint8_t *) header, sizeof(FileHeader));
    //if bytes read is not equal to the size of the file header, print error message and exit
    if (bytes_read != sizeof(FileHeader)) {
        fprintf(stderr, "Bad magic number.\n");
        exit(1);
    }
    if (big_endian()) { //if big endian, swap endianness
        header->magic = swap32(header->magic); //swap magic number of header
        header->protection = swap16(header->protection); //swap protection of header
    }
    //if magic number is incorrect, print error message and exit
    if (header->magic != MAGIC) {
        fprintf(stderr, "Bad magic number.\n");
        exit(1);
    }
}

void write_header(int outfile, FileHeader *header) {
    //write bytes to outfile
    int bytes_written = write_bytes(outfile, (uint8_t *) header, sizeof(FileHeader));
    //if bytes written is not equal to the size of the file header, print error message and exit
    if (bytes_written != sizeof(FileHeader)) {
        fprintf(stderr, "Could not write to file header");
        exit(1);
    }
    if (big_endian()) {
        header->magic = swap32(header->magic); //swap magic number of header
        header->protection = swap16(header->protection); //swap protection of header
    }
}

static uint8_t buf[BLOCK]; //create a buffer with size of block

//lev(tutor) helped me with this function
bool read_sym(int infile, uint8_t *sym) {
    static int current = 0; //index of block
    static int size = 0; //size of block
    if (current == size) { //if index of block is equal to size of block
        size = read_bytes(infile, buf, BLOCK); //read in bytes from infile into buffer
        current = 0; //reset index of block to 0
    }
    if (current < size) { //if index of block is less than size of block
        *sym = buf[current]; //set sym to the current index of the buffer
        current++; //increment index of block
        return true; //return true
    }
    return false; //return false
}

static uint8_t write_buffer[BLOCK]; //create a buffer with size of block
static int index = 0; //index of block

//lev(tutor) helped me write this helper function for write_pair()
static void write_bit(int outfile, uint8_t bit) {
    if (bit == 1) { //if bit is 1, set bit to 1
        write_buffer[index / 8] |= (1 << (index % 8));
    } else { //if bit is 0, set bit to 0
        write_buffer[index / 8] &= ~(1 << (index % 8));
    }
    index++; //increment index of block
    //if index of block is equal to size of block, write bytes to outfile
    if (index == BLOCK * 8) {
        write_bytes(outfile, write_buffer, BLOCK);
        index = 0; //reset index of block to 0
    }
}

//lev(tutor) helped me with this function
void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    //write code to outfile
    for (int i = 0; i < bitlen; i++) { //for each bit in the code
        write_bit(outfile, (code >> i) & 1); //write bit to outfile
    }
    //write symbol to outfile
    for (int i = 0; i < 8; i++) { //for each bit in the symbol
        write_bit(outfile, (sym >> i) & 1); //write bit to outfile
    }
}

//dev(TA) helped me with this function
void flush_pairs(int outfile) {
    //write out any remaining pairs of symbols and codes to the output file
    int bytes = index / 8; //number of bytes
    if (index % 8 != 0) { //if index of block is not divisible by 8
        bytes++; //increment number of bytes by 1
    }
    write_bytes(outfile, write_buffer, bytes); //write bytes to outfile
}

//lev(tutor) helped me with this function
static bool read_bit(int infile, uint8_t *bit) {
    static int read_index = 0; //set read index to 0
    static uint8_t read_buffer[BLOCK]; //create a buffer with size of block
    static int length = 0; //set length to 0
    //if read index is 0 or read index is equal to length * 8
    if (read_index == 0 || read_index == length * 8) {
        //read in bytes from infile into buffer
        int num_read_bytes = read_bytes(infile, read_buffer, BLOCK);
        read_index = 0; //reset read index to 0
        length = num_read_bytes; //set length to number of bytes read
    }
    //if length is 0, return false
    if (length == 0) {
        return false;
    }
    //set bit to the read index of the buffer
    *bit = (read_buffer[read_index / 8] >> (read_index % 8)) & 1;
    read_index++; //increment read index
    return true; //return true
}

//lev(tutor) helped me with this function
bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    uint8_t track_bit = 0; //set track_bit to 0
    *code = 0; //initialize code to 0 before reading
    //read code from buffer
    for (int i = 0; i < bitlen; i++) { //for each bit in the code
        read_bit(infile, &track_bit);
        if (track_bit) //if track_bit is 1
            *code |= 1 << i; //set ith bit of code to 1
        else {
            *code &= ~(1 << i); //set ith bit of code to 0
        }
    }
    //read symbol from buffer
    for (int i = 0; i < 8; i++) { //for each bit in the symbol
        read_bit(infile, &track_bit);
        if (track_bit) { //if track_bit is 1
            *sym |= 1 << i; //set ith bit of sym to 1
        } else {
            *sym &= ~(1 << i); //set ith bit of sym to 0
        }
    }
    //if code is equal to stop code, return false
    if (*code == STOP_CODE) {
        return false;
    }
    return true; //return true
}

static uint8_t write_word_buffer[BLOCK]; //create a buffer with size of block
static int word_index = 0; //set word index to 0

//miles(tutor) helped me with this function
void write_word(int outfile, Word *w) {
    for (uint32_t i = 0; i < w->len; i++) { //for each symbol in the word
        write_word_buffer[word_index] = w->syms[i]; //set word_index of buffer to symbol
        word_index++; //increment word index by 1
        //if word index is equal to size of block
        if (word_index == BLOCK) {
            write_bytes(outfile, write_word_buffer, BLOCK); //write bytes to outfile
            word_index = 0; //reset word_index to 0
        }
    }
}

void flush_words(int outfile) {
    //writes out any remaining symbols in the buffer to the outfile
    write_bytes(outfile, write_word_buffer, word_index); //write bytes to outfile
}
