#include "types.h"

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <time.h>

#include <string.h>
#include <math.h>

#include "cardFuncs.h"





	// Card testR[3] = {
	// 	{CLUBS, 1},
	// 	{CLUBS, 2},
	// 	{CLUBS, 3}
	// };

	// printf("%s\n", isRun(testR, 3) ? "In Run" : "Not in Run");


	// Card testS[3] = {
	// 	{CLUBS, 1},
	// 	{HEARTS, 1},
	// 	{DIAMONDS, 1}
	// };

	// printf("%s\n", isSet(testS, 3) ? "In Set" : "Not in Set");


	// printf("%s\n", isMeld(testS, 3) ? "In Meld" : "Not in Meld");
	// printf("%s\n", isMeld(testR, 3) ? "In Meld" : "Not in Meld");




//bool areCardsInRow(Card cards[], int size) {}
bool isMeld(Card cards[], int size) {

	//TODO

	/*
		So the rules are in order numebers of the same suit, or 3 - 4 of the same number of diffrenct suit's
	*/

	//size shouldnt be higher then 4

	return isRun(cards, size) || isSet(cards, size);
}



bool isSet(Card cards[], int size) {

	//This can only be four in size (I hope)

	Card priv;

	for (int i = 0; i < size; i++) {
		if (i == 0) {
			priv = cards[i];
			continue;
		}
		if (priv.number != cards[i].number) {
			return false;
		}
	}

	return true;
	
}



int comparCard (const void* e1, const void* e2) {
	//All credit to this stackover question
	//https://stackoverflow.com/questions/1787996/c-library-function-to-perform-sort

	Card a = *((Card*)e1);
	Card b = *((Card*)e2);

	if (a.number > b.number)
		return 1;
	if (a.number < b.number)
		return -1;
	return 0;
}


bool isRun(Card cards[], int size) {
	//https://stackoverflow.com/questions/1787996/c-library-function-to-perform-sort


	//Cards of the same suit that are incremental
	//Size should not be bigger then 4 ever, (?)

	
	//is [n] < [n+1] ?
	//memcpy()

	//MAKE SURE TO FREE THIS
	Card* tempSortArray = (Card*) malloc(sizeof(Card) * size);
	if (tempSortArray == NULL) {
		perror("Fatal: Failed to allocate room for tempSortArray (function isRun in cardFuncs)\n");
		exit(EXIT_FAILURE);
	}

	memcpy(tempSortArray, cards, sizeof(Card) * size);

	qsort(tempSortArray, size, sizeof(Card*), comparCard);

	//MAKE SURE THEY ARE ALL SAME SUIT, TODO

	int priv = 0;
	Suit privS;
	for(int i = 0; i < size; i++) {
		//pCard(tempSortArray[i]);
		
		if (i == 0) {
			priv = tempSortArray[i].number;
			privS = tempSortArray[i].suit;
			continue;
		}
		if ( tempSortArray[i].number - priv != 1  || tempSortArray[i].suit != privS) {
			//The card is NOT exactly 1 higher then the last
			free(tempSortArray); //Make sure to free that
			return false;
		}
		//printf("i %d, priv %d, comp: %d\n", i, priv, tempSortArray[i].number - priv == 1);
		priv = tempSortArray[i].number;
		privS = tempSortArray[i].suit;
	}

	//If we get here ig we all good
	free(tempSortArray);
	return true;


}

























