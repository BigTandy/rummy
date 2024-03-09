#include "types.h"


#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <time.h>

#include "deckFuncs.h"



void genDeck(Card cardArray[]/*, int arrSize*/) {
	/*
		Takes a card array and builds standard 52 card dec
	*/
	int i, j, number = 0;

	for(i = 1; i <= 13; i++) {
		//Iterate over card numbers

		for(j = 1; j < 5; j++) {
			//Iterate over suit's

			Card new = {j, i};

			cardArray[number] = new;

			//printf("N: %d, S: %d, F: %d\n", i, j, number);
			number++;
		}
		
	}


	//printf("MAX %d\n", number);

   return;
}



void shuffle(Card deck[], int size) {
	//https://stackoverflow.com/questions/5064379/generating-unique-random-numbers-in-c
	//https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle

	int j;
	Card temp;
	for(int i = size - 1; i > 0; i--) {
		//0 <= j <= i
		j = (
			rand() % ((i - 0) + 1) + 0
		);
		//The swap
		temp = deck[i];
		deck[i] = deck[j];
		deck[j] = temp;
	}

	return;
}


void dealHand(Card deck[], Card hand1[], Card hand2[]) {


	//You go back and forth dealing
	
	//Need 7 cahds per player, 7 * players (2)

	int p1_noc = 0;
	int p2_noc = 0;

	for(int i = 14; i > 0; i--) {

		//need to pop cards off deck and insert them into hands
		if (i % 2 == 0) {
			hand1[p1_noc] = deckPop(deck, 52);
			p1_noc++;
		} else {
			hand2[p2_noc] = deckPop(deck, 52);
			p2_noc++;
		}

		if(p1_noc > 7 || p2_noc > 7) {
			fprintf(stderr, "Dealer handed out more then 7 cards to a player\n");
			//exit(EXIT_FAILURE);
		}

	}


	return;
}


void dumpHand(Card hand[], bool newLine) {


	//Get length of hand
	int i = 0;
	while(hand[i].number != 0 && hand[i].suit != JOKER) {
		i++;
	}

	if (i == 0)
		return;


	for(int j = 0; j < i; j++) {
		printf("(%c%c) ", numChar(hand[j].number), suitChar(hand[j].suit));
		if ((j + 1) % 7 == 0) {
			printf("\n");
			for(int l = 6; l >= 0; l--) {
				printf(" %.2d  ", j - l);
			}
			printf("\n");
		}

		/*
			Spent way too much fucking time making this display how I wanted and it looks meh
			Actually going to self immolate lmao
			It is 2:18 am rn and I am t i r e d

			Nevermind, it looks goodish now!! yay :)
		*/
		
		if (j == i - 1 && (j + 1) % 7 != 0) {
			printf("\n");
			for(int l = (j) % 7; l >= 0; l--) {
				printf(" %.2d  ", j - l);
			}
		}
	}



	if (newLine)
		printf("\n");
}



bool deckPush(Card deck[], int dSize, Card card) {
	//Returns how ever many appeneded

	//Hopfully this works lmao

	for(int i = 0; i < dSize; i++) {
		if(
			deck[i].suit == JOKER &&
			deck[i].number == 0
		) {

			//printf("i, Found free %d\n", i);

			deck[i] = card;
			return true;
		}
	}
	

	return false;
}


int deckPushs(Card deck[], int dSize, cardU cards, int cSize) {
	//Returns how ever many appeneded

	//Hopfully this works lmao


	int cDown = cSize;
	int filled = 0;

	for(int i = 0; i < dSize; i++) {
		if(
			deck[i].suit == JOKER &&
			deck[i].number == 0
		) {

			//printf("i, Found free %d\n", i);
			if (cSize == 1) {
				deck[i] = cards.card;
			}

			if (cDown > 0) {

				deck[i] = deckPop(cards.cardP, cSize);
				filled++;
				cDown--;
			}
		}
	}
	

	return filled;
}


Card deckPop(Card deck[], int size) {

	Card temp;
	for(int i = size - 1; i > 0; i--) {
		if(
			deck[i].suit != JOKER &&
			deck[i].number != 0
		) {
			temp = deck[i];
			deck[i].suit = JOKER;
			deck[i].number = 0;
			return temp;
		}
	}

}



void dumpDeck(Card deck[]) {
	//Card
	printf("  +0   +1   +2   +3\n");
	for(int i = 0; i < 52; i++){
		printf("(%c%c) ", numChar(deck[i].number), suitChar(deck[i].suit));
		if( (i + 1) % 4 == 0) {
			printf(" %.2d\n", i);
		}
	}
	return;
}


















