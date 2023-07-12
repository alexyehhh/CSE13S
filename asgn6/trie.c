#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "trie.h"
#include "code.h"

TrieNode *trie_node_create(uint16_t index) {
    TrieNode *node = malloc(sizeof(TrieNode)); //allocates memory for a new node
    if (node == NULL) { //if the node is NULL
        return NULL;
    }
    node->code = index; //the node's code is set to code
    for (int i = 0; i < ALPHABET; i++) { //for each child of the node
        node->children[i] = NULL; //set each child node pointer to NULL
    }
    return node; //return the node
}

void trie_node_delete(TrieNode *n) {
    free(n); //frees the memory allocated for the node
}

TrieNode *trie_create(void) {
    TrieNode *root = trie_node_create(EMPTY_CODE); //creates a new node with the code EMPTY_CODE
    if (root == NULL) { //if the root is NULL
        return NULL; //return NULL
    }
    return root; //return the root
}

void trie_reset(TrieNode *root) {
    for (int i = 0; i < ALPHABET; i++) { //for each child of the root
        trie_node_delete(root->children[i]); //delete each child
        root->children[i] = NULL; //set each of the root's children to NULL
    }
}

void trie_delete(TrieNode *n) {
    for (int i = 0; i < ALPHABET; i++) { //for each child of the node
        if (n->children[i] != NULL) { //if the child is not NULL
            trie_delete(n->children[i]); //delete the child
            n->children[i] = NULL; //set the child to NULL
        }
    }
    trie_node_delete(n); //delete the node
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    if (n->children[sym] == NULL) { //if the child is NULL
        return NULL; //return NULL
    }
    return n->children[sym]; //return the child representing the symbol sym
}
