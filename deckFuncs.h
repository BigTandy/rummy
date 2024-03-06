#pragma once

#include "types.h"



void genDeck(Card[]);
void shuffle(Card deck[], int size);
void dumpDeck(Card deck[]);

bool deckPush(Card deck[], int size, Card cd);
void dealHand(Card deck[], Card hand1[], Card hand2[]);
Card deckPop(Card deck[], int size);
void dumpHand(Card hand[], bool newLine);





