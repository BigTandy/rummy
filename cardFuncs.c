#include "types.h"

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <time.h>

#include <string.h>
#include <math.h>

#include "cardFuncs.h"



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
		perror("Fatal: Failed to allocate room for tempSortArray\n");
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

























