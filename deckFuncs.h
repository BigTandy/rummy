#pragma once

#include "types.h"


typedef union cardU {
	Card* cardP;
	Card  card;
} cardU;


void genDeck(Card[]);
void shuffle(Card deck[], int size);
void dumpDeck(Card deck[]);

bool deckPush(Card deck[], int dSize, Card card);
int deckPushs(Card deck[], int dSize, cardU cards, int cSize);

void dealHand(Card deck[], Card hand1[], Card hand2[]);
Card deckPop(Card deck[], int size);
void dumpHand(Card hand[], bool newLine);





