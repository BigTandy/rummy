#include "clist.h"
#include <stdlib.h>
#include <stdio.h>

// typedef enum suit {
//     JOKER = 0, CLUBS, HEARTS, SPADES, DIAMONDS
//     //Even = Red, Odd = Black; JOKER is kinda like null card
// } Suit;

// typedef struct card {
//     Suit suit;
//     int number; //A = 1 & 14, 10 = T, 11 = J, 12 = Q, 13 = K
// } Card;



// typedef struct cNode {
//     Card data;

//     cNode* next;
//     cNode* priv;
//     cNode* head;
//     cNode* tail;
// } cNode;


cNode* newNode() {

    cNode* list = (cNode*) malloc(sizeof(cNode));
    
    if (list == NULL) {
        //We failed...
        perror("Fatal: Failed to allocate space for list");
        exit(EXIT_FAILURE);
    }

    
    list->data.suit = JOKER;
    list->data.number = 0;

    list->next = NULL;
    list->priv = NULL;

    list->head = NULL;
    list->tail = NULL;

    return list;
}


void freeNode(cNode* node) {

    cNode* tnext;
    tnext = node->next;
    node->next = node->tail;
    node->tail = tnext;

    free(node);

    return;
}


void appendNode();