#pragma once

#include "types.h"



int deckSize(Card deck[]);
void genDeck(Card[]);

void shuffle(Card deck[], int size);
void dumpDeck(Card deck[]);

int deckPush(Card deck[], int dSize, Card card);
void dealHand(Card deck[], Card hand1[], Card hand2[]);

Card deckPop(Card deck[], int size);
void dumpHand(Card hand[], bool newLine);


//int deckPushs(Card deck[], int dSize, cardU cards, int cSize);


