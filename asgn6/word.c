#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "word.h"
#include "code.h"

Word *word_create(uint8_t *syms, uint32_t len) {
    Word *word = malloc(sizeof(Word)); //allocate memory for a word
    if (word == NULL) { //if the word is NULL
        free(word); //free the memory allocated for the word
        return NULL; //return NULL
    }
    word->syms = malloc(len * sizeof(uint8_t)); //allocate memory for the array of symbols
    if (word->syms == NULL) { //if the array of symbols is NULL
        free(word); //free the memory allocated for the array of symbols
        return NULL; //return NULL
    }
    word->len = len; //set the length of the word
    for (uint32_t i = 0; i < len; i++) { //for each symbol in the array of symbols
        word->syms[i]
            = syms[i]; //copy the symbol from the array of symbols to the word's array of symbols
    }
    return word; //return the word
}

Word *word_append_sym(Word *w, uint8_t sym) {
    uint32_t len = 0; //set length variable to zero
    if (w != NULL) { //if the word is not NULL
        len = w->len; //set the length variable to the length of the word
    }
    len++; //increase the length by one
    Word *newWord = malloc(sizeof(Word)); //allocates memory for a new word
    if (newWord == NULL) { //if the word is NULL
        free(newWord); //free the memory allocated for the word
        return NULL; //return NULL
    }
    newWord->syms = malloc((len) * sizeof(uint8_t)); //allocates memory for the array of symbols
    if (newWord->syms == NULL) { //if the array of symbols is NULL
        free(newWord); //free the memory allocated for the array of symbols
        return NULL; //return NULL
    }
    newWord->len = len; //set the length of the new word to the length of the old word plus one
    for (uint32_t i = 0; i < len - 1; i++) { //for each symbol in the array of symbols
        newWord->syms[i]
            = w->syms
                  [i]; //copy the symbols from the array of symbols to the word's array of symbols
    }
    newWord->syms[len - 1] = sym; //appends the symbol to the end of the array of symbols
    return newWord; //return the word
}

void word_delete(Word *w) {
    free(w->syms); //frees the memory allocated for the array of symbols
    free(w); //frees the memory allocated for the word
}

WordTable *wt_create(void) {
    WordTable *wt = calloc(MAX_CODE, sizeof(Word *)); //allocates memory for a new word table
    //calloc is used here to initialize the WordTable to all NULL values
    if (wt == NULL) { //if the word table is NULL
        return NULL; //return NULL
    }
    wt[EMPTY_CODE] = word_create(
        NULL, 0); //sets the word at index EMPTY_CODE to the empty word, a string of length of zero
    return wt; //return the word table
}

void wt_reset(WordTable *wt) {
    //resets a WordTable, wt, to contain just the empty Word.
    for (int i = 0; i < MAX_CODE; i++) { //for each word in the word table
        if (i != EMPTY_CODE
            && wt[i] != NULL) { //if the word is not the empty word and the word is not NULL
            word_delete(wt[i]); //frees the memory allocated for each word in the word table
            wt[i] = NULL; //sets each word in the word table to NULL
        }
    }
}

void wt_delete(WordTable *wt) {
    for (int i = 0; i < MAX_CODE; i++) {
        if (wt[i] != NULL) {
            word_delete(wt[i]); //frees the memory allocated for each word in the word table
        }
    }
    free(wt); //frees the memory allocated for the word table
}
