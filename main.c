#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <time.h>

// #include <sys/socket.h>
// #include <sys/types.h>

// #include <netinet/in.h>
// #include <arpa/inet.h>



/*
Rummy, 52 card deck
Every player gets 7 cards
A 2 3 4 5 6 7 8 9 + J Q K





*/


#include "types.h"
#include "deckFuncs.h"



void pCard(Card c);
void getUserCommand(Card deck[], Card discard[], pState p1, pState p2);

void discardCardAction(void);
void placeCardAction(void);

void printUsage(void);
void pickupCardAction(void);


// const char TEN = 'T';
// const char JACK = 'J';
// const char QUEEN = 'Q';
// const char KING = 'K';
// const char ACE = 'A';





int main(int argc, char* argv[]) {


	//Seed the random machine
	srand((unsigned) time(NULL));

	Card deck[52];
	Card discard[52] = {JOKER, 0};
	genDeck(deck);

	//Can you shuggle the cahds
	shuffle(deck, 52);


	//Need to gen players
	//Shufle dec?

	//Assume two players
	//52 & 7 == 3


	//Need to keep state together?
	//^^^ TODO, Keep in mind for I.2

	Card PlayerHand[52] = {JOKER, 0};
	Card inPlay_Player[52] = {JOKER, 0};
	pState Player = {PlayerHand, inPlay_Player};

	Card ComputerHand[52] = {JOKER, 0};
	Card inPlay_Computer[52] = {JOKER, 0};
	pState Computer = {ComputerHand, inPlay_Computer};

	
	//Dealing alternates tho...
	dealHand(deck, Player.hand, Computer.hand);

	/*
		TODO:
		Clean up and organize code
		Organize it into a "card game" engine
	*/


	//Todo, add a single card to the discard pile, and display that
	

	discard[0] = deckPop(deck, 52); //Switch to deckPush()
	

	//'Game' loop
	bool luup = true;
	int LOC;

	while(luup) {
		
		printf("Your Hand:\n");
		dumpHand(Player.hand, true);

		printf("Discard Pile:\n");
		dumpHand(discard, true);

		printf("In Play:\n");
		printf("\tYou:\n");
		dumpHand(Player.inPlay, true);

		getUserCommand(deck, discard, Player, Computer);



		//luup = false;


	}



	return 0;
}


//bool areCardsInRow(Card cards[], int size) {}
bool areCardsInRow(Card cards[], int size) {

	/*
		So the rules are in order numebers of the same suit, or 3 - 4 of the same number of diffrenct suit's
	*/

	int inrow = 0;
	for(int i = 0; i < size; i++) {

	}
}


void getUserCommand(Card deck[], Card discard[], pState p1, pState p2) {

	int LOC;
	char in;

	do {
		printf("> ");
		LOC = scanf(" %c", &in);
	} while(LOC != 1);

	switch (in) {
	
	case 'P':
	case 'p':
		//Pickup Card, call its function
		/*
			P
			(D)eck or D(i)scard?
			D takes no args, pops card off deck into hand, shows you, and then you can Discard to end your turn

			I will ask you which number card in the discard pile, (that number and up)
				Have to use that card if not [-1], if cant, forced to return stack
			
		*/
		pickupCardAction();
		break;
	
	case 'D':
	case 'd':
		//Discard card to end turn
		discardCardAction();
		break;

	case 'L':
	case 'l':
		//Place down cards
		placeCardAction();
		break;

	case 'B':
	case 'b':
		printf("Deck:\n");
		dumpDeck(deck);

		printf("\nDiscard:\n");
		dumpDeck(discard);

		printf("\nP1:\n");
		dumpDeck(p1.hand);

		printf("\nP2:\n");
		dumpDeck(p2.hand);
		break;
	
	case 'Q':
	case 'q':
		exit(0);

	default:
		//Invalid input, print usage
		printUsage();
		break;
	}
	

	

}


/*
	TODO:
	Build out these functions
*/
void discardCardAction(void) {}
void placeCardAction(void) {}
void printUsage(void) {}
void pickupCardAction(void) {}




void pCard(Card c) {
	printf("(%c%c)", numChar(c.number), suitChar(c.suit));
	return;
}


