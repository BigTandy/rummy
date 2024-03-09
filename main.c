#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <time.h>

#include <string.h>
#include <math.h>

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

#include "cardFuncs.h"





void pCard(Card c);
void getUserCommand(gState Game);

void discardCardAction(gState Game);
void placeCardAction(gState Game);

void pickupCardAction(gState Game);
void printUsage(void);

void start_turn(gState Game);
void process_turn(gState Game);
void end_turn(gState Game);

bool isMeld(Card cards[], int size);


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

	//The Game State
	gState Game = {Player, Computer, deck, discard};


	/*
		TODO:
		Clean up and organize code
		Organize it into a "card game" engine
	*/


	//Todo, add a single card to the discard pile, and display that
	

	//discard[0] = deckPop(deck, 52); //Switch to deckPush()
	deckPush(discard, 52, deckPop(deck, 52));

	
	

	//'Game' loop
	bool luup = true;
	int LOC;

	/*
		Need to keep state on whos turn it is,
		And to release the turn you need to discard

		Who is [In Play] (After picked up, before discarded)
	*/



	//whoInPlay who = PLAYER;
	//isReady handState = BEFORE_PICKUP;

	Game.Who = PLAYER;
	Game.turnState = notStarted;

	// Card test[3] = {
	// 	{CLUBS, 1},
	// 	{CLUBS, 2},
	// 	{CLUBS, 3}
	// };

	// printf("%s\n", isRun(test, 3) ? "In Run" : "Not in Run");


	/*
	Before pickup -> pickup_handler(who)	
	*/



	//Player has to begin turn by picking up,
	//Player then can play if they want,
	//Player must end turn by discarding, ending the game if that was their last card

	while(luup) {


		switch (Game.turnState) {

			case notStarted:
				//Ask player to pickup
				start_turn(Game);
				Game.turnState = inPlay;
				break;
			case inPlay:
				//Ask and process game
				process_turn(Game);
				break;
			case discarded:
				//Cleanup at turn end, and check if end-of-game
				end_turn(Game);
				break;


		}


	}



	return 0;
}



	



bool isSet(Card cards[], int size) {

	//This can only be four in size

	


	
}


//bool areCardsInRow(Card cards[], int size) {}
bool isMeld(Card cards[], int size) {

	//TODO

	/*
		So the rules are in order numebers of the same suit, or 3 - 4 of the same number of diffrenct suit's
	*/

	//size shouldnt be higher then 4

	return isRun(cards, size) || isSet(cards, size);
}




void start_turn(gState Game) {

	//Tell user the table state and their hand
	//Tell them to pickup (-1 for deck, # for discard)(?)
	//Switch turn-state to 'in play'

	//Need function to return correct array for current player & Func to return right string for c-player

	//REPLACE SOMETIME
	if(Game.Who == PLAYER)
		printf("Player 1\n");
	else
		printf("Player 2\n");
	
	
	printf("Your hand:\n");
	dumpHand(getCurrentPlayer(Game).hand, true);

	printf("Your Cards In Play\n");
	dumpHand(getCurrentPlayer(Game).inPlay, true);

	printf("Discard Pile\n");
	dumpHand(Game.Discard, true);

	printf("Pickup from (D)eck or D(i)scard? ");

	char c;
	scanf(" %c", &c);

	if (c == 'D' || c == 'd') {
		int worked;

		worked = deckPush(getCurrentPlayer(Game).hand, 52, deckPop(Game.Deck, 52));
		//printf("Filled, %d\n", worked);

	} else if (c == 'I' || c == 'i') {
		printf("Number ");
		int discardPickup;
		scanf("%d", &discardPickup);
		//Do logic for picking up cards from discard
		//Force player to use the lowest picked up card if not (c == 0), if they dont, return cards
		//TODO ^^^
	}



	return;
}

void process_turn(gState Game) {

	//Play cards or end turn (blank char?)

	//printf("\n");
	
	char c;
	scanf(" %c", &c);


	return;
}


void end_turn(gState Game) {



	return;
}









// void getUserCommand(gState Game) {

// 	int LOC;
// 	char in;

// 	do {
// 		printf("> ");
// 		LOC = scanf(" %c", &in);
// 	} while(LOC != 1);

// 	switch (in) {
	
// 	case 'P':
// 	case 'p':
// 		//Pickup Card, call its function
// 		/*
// 			P
// 			(D)eck or D(i)scard?
// 			D takes no args, pops card off deck into hand, shows you, and then you can Discard to end your turn

// 			I will ask you which number card in the discard pile, (that number and up)
// 				Have to use that card if not [-1], if cant, forced to return stack
			
// 		*/
// 		pickupCardAction(Game);
// 		break;
	
// 	case 'D':
// 	case 'd':
// 		//Discard card to end turn
// 		discardCardAction(Game);
// 		break;

// 	case 'L':
// 	case 'l':
// 		//Place down cards
// 		placeCardAction(Game);
// 		break;

// 	case 'B':
// 	case 'b':
// 		printf("Deck:\n");
// 		dumpDeck(Game.Deck);

// 		printf("\nDiscard:\n");
// 		dumpDeck(Game.Discard);

// 		printf("\nP1:\n");
// 		dumpDeck(Game.Player.hand);

// 		printf("\nP1 IP:\n");
// 		dumpDeck(Game.Player.inPlay);

// 		printf("\nP2:\n");
// 		dumpDeck(Game.Computer.hand);

// 		printf("\nP2 IP:\n");
// 		dumpDeck(Game.Computer.inPlay);

// 		printf("\n\n");
// 		break;
	
// 	case 'Q':
// 	case 'q':
// 		exit(0);

// 	default:
// 		//Invalid input, print usage
// 		printUsage();
// 		break;
// 	}
	

	

// }






void pCard(Card c) {
	printf("(%c%c)", numChar(c.number), suitChar(c.suit));
	return;
}


