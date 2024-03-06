#ifndef CLIST_H
#define CLIST_H











typedef enum suit {
    JOKER = 0, CLUBS, HEARTS, SPADES, DIAMONDS
    //Even = Red, Odd = Black; JOKER is kinda like null card
} Suit;

typedef struct card {
    Suit suit;
    int number; //A = 1 & 14, 10 = T, 11 = J, 12 = Q, 13 = K
} Card;



typedef struct cNode {
    Card data;
    
    cNode* next;
    cNode* priv;
    cNode* head;
    cNode* tail;
} cNode;










#endif