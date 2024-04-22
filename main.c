#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <time.h>

#include <string.h>
#include <math.h> //https://stackoverflow.com/a/5248968

#include <termios.h>
#include <ctype.h>

#include <signal.h>

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
#include "util.h"




void pCard(Card c);
void start_turn(gState* Game);

void process_turn(gState* Game);
void end_turn(gState* Game);



// const char TEN = 'T';
// const char JACK = 'J';
// const char QUEEN = 'Q';
// const char KING = 'K';
// const char ACE = 'A';




extern __ssize_t getline(char **__restrict __lineptr, size_t *n, FILE *stream);


int main(int argc, char* argv[]) {


	//gcc main.c deckFuncs.c types.c cardFuncs.c util.c -lm -g


	//Seed the random machine
	srand((unsigned) time(NULL));

	Card deck[DECK_SIZE];
	Card discard[DECK_SIZE] = {JOKER, 0};
	genDeck(deck);

	shuffle(deck, DECK_SIZE);

	//Need to gen players
	//Shufle dec?

	//Assume two players
	//52 & 7 == 3


	//Need to keep state together?
	//^^^ TODO, Keep in mind for I.2

	Card PlayerHand[DECK_SIZE] = {JOKER, 0};
	Card inPlay_Player[DECK_SIZE] = {JOKER, 0};

	pState Player;// = {PlayerHand, inPlay_Player};
	Player.hand = PlayerHand;
	Player.inPlay = inPlay_Player;
	Player.amountRuns = 0;
	
	for(int i = 0; i < DECK_SIZE; i++) {
		Player.ipRuns[i] = (Run) {{JOKER, 0}};
	}


	Card ComputerHand[52] = {JOKER, 0};
	Card inPlay_Computer[52] = {JOKER, 0};

	pState Computer;// = {ComputerHand, inPlay_Computer};
	Computer.hand = ComputerHand;
	Computer.inPlay = inPlay_Computer;
	Computer.amountRuns = 0;

	for(int i = 0; i < DECK_SIZE; i++) {
		Computer.ipRuns[i] = (Run) {{JOKER, 0}};
	}


	
	//Dealing alternates tho...
	dealHand(deck, Player.hand, Computer.hand);

	//The Game State
	gState Game = {Player, Computer, deck, discard};



	deckPush(discard, DECK_SIZE, deckPop(deck, DECK_SIZE));

	
	

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



	// printf("PH: %d\n", deckSize(PlayerHand));
	// printf("CH: %d\n", deckSize(ComputerHand));
	// printf("DS: %d\n", deckSize(deck));
	// printf("IS: %d\n", deckSize(discard));


	/*
	Before pickup -> pickup_handler(who)	
	*/



	//Player has to begin turn by picking up,
	//Player then can play if they want,
	//Player must end turn by discarding, ending the game if that was their last card

	//TODO, need point mapping for cards

	while(luup) {


		switch (Game.turnState) {

			case notStarted:
				//Ask player to pickup
				start_turn(&Game);
				Game.turnState = inPlay;
				break;
			case inPlay:
				//Ask and process game
				process_turn(&Game);
				Game.turnState = turnEnded;
				//Game.turnState = notStarted;
				break;
			case turnEnded:
				//End turn and discard
				end_turn(&Game);
				//Need to switch player and tState

				if (Game.Who == PLAYER) {
					Game.Who = COMPUTER;
				} else if (Game.Who == COMPUTER) {
					Game.Who = PLAYER;
				}



				Game.turnState = notStarted;
				break;

		}


	}



	return 0;
}















void start_turn(gState* Game) {

	//Tell user the table state and their hand
	//Tell them to pickup (-1 for deck, # for discard)(?)
	//Switch turn-state to 'in play'

	//Need function to return correct array for current player & Func to return right string for c-player

	//REPLACE SOMETIME
	if(Game->Who == PLAYER)
		printf("Player 1\n");
	else
		printf("Player 2\n");
	

	//Fix the fucking spacing wtf (newlines)
	
	printf("Your hand:\n");
	dumpHand(getCurrentPlayer(Game)->hand, true);

	//Make this show runs for cards in play
	printf("Your Cards In Play:\n");
	dumpInPlay(*getCurrentPlayer(Game));

	printf("Their Cards In Play:\n");
	dumpInPlay(*getOtherPlayer(Game));

	printf("Discard Pile:\n");
	dumpHand(Game->Discard, true);



	// //TODO, make this way better lmao;
	// //Remove this
	// printf("Runs: %d\n", getCurrentPlayer(Game)->amountRuns);
	// for (int i = 0; i < getCurrentPlayer(Game)->amountRuns; i++) {

	// 	printf("Run #%d: %d\n", i, getCurrentPlayer(Game)->ipRuns[i].size);

	// 	for (int j = 0; j < getCurrentPlayer(Game)->ipRuns[i].size; j++) {
	// 		pCard(getCurrentPlayer(Game)->ipRuns[i].runCards[j].card);
	// 		printf("I: %d\n", getCurrentPlayer(Game)->ipRuns[i].runCards[j].index);
	// 	}
	// 	printf("---\n");
	// }

	

	//TODO, Print out hand after picking up a card!! <---

	char c;
	do {
		printf("Pickup from (D)eck or D(i)scard? ");
		scanf(" %c", &c);
		flushKeyboard();
	} while (c != 'D' && c != 'd' && c != 'I' && c != 'i');


	if (c == 'D' || c == 'd') {

		deckPush(getCurrentPlayer(Game)->hand, 52, deckPop(Game->Deck, 52));


	} else if (c == 'I' || c == 'i') {

		//TODO REPLACE WITH GETCARDNUMBER
		printf("Number ");
		int discardPickup;
		scanf("%d", &discardPickup);
		flushKeyboard();
		//Do logic for picking up cards from discard
		//Force player to use the lowest picked up card if not (c == 0), if they dont, return cards
		//TODO ^^^
	}



	return;
}


int comparInt (const void* e1, const void* e2) {

	int a = *((int*)e1);
	int b = *((int*)e2);

	if (a > b)
		return -1;
	if (a < b)
		return 1;
	return 0;
}


void playCards(gState* Game) {

	//Left off here,
	// March 9th 2024 1:02 AM
	/*
		Need to get from the user what cards they want to play,
		if those form a meld (Play cards on other players aswell, todo) (play cards onto their own inPlay aswell, todo)
		and then actually play the cards into the players `currentPlayer().inPlay` deck
		return to process_turn (Actually jump back to the top, or restart question loop, so player can play multiple times)
	
	
	*/

	//Get cards numbers from user


	// //Make sure the user knows their most current hand
	// printf("\n----------\nYour hand:\n");
	// dumpHand(getCurrentPlayer(Game)->hand, true);



	/*
	==========	   (-----)		I----)		  (-----)
		I		  (       )		I-----)		 (       )
		I		 (         )	I------)	(         )
		I		  (       )		I-----)		 (       )
		I		   (-----)		I----) 		  (-----)
	*/






	int buff[DECK_SIZE];
	int ibuffSize = DECK_SIZE;


	int currPlayerDeckSize = deckSize(getCurrentPlayer(Game)->hand);


	askForCardNumbers:

	//Need to wipe buffer
	for(int i = 0; i < ibuffSize; i++) {
		buff[i] = -1;
	}

	getCardNumbers(buff, ibuffSize);



	//Get size of returned card numbers

	//Make func?
	int returned_buff_size = 0;

	while (buff[returned_buff_size] >= 0) {
		returned_buff_size++;
	}

	//We need to sort and reverse `buff` so when we remove cards from the hand, we dont modify the data we are working on
	//Bandaid solution ik, but ill fix later, 11:30 PM rn so I just want it to work


	#ifdef DEBUG
	for (int i = 0; i < DECK_SIZE; i++) {
		printf("%d ", buff[i]);
	}
	printf("\n");
	#endif


	//We must find out if the user wants to play cards on themselves or other
	//How do we play cards on existing run
	//Deck metadata? Run Numbers?

	//TODO
	if (returned_buff_size < 3) {
		//Not enough cards to play for a normal hand

	}



	for(int i = 0; i < returned_buff_size; i++) {
		if (buff[i] > currPlayerDeckSize) {
			printf("Incorrect hand number or amount of cards\n");
			goto askForCardNumbers;  //TODO, GOTO
		}
	}



	//Need to grab those cards, put them in a new *dynamicly* allocated array (Because the size)

	// for (int i = 0; i < returned_buff_size; i++) {
	// 	printf("%d, (%c, %c)\n", buff[i],
	// 	numChar(getCurrentPlayer(Game).hand[buff[i]].number), suitChar(getCurrentPlayer(Game).hand[buff[i]].suit));
	// }


	// BE SURE TO FREE THIS
	Card* tempCardBuffer = (Card*) malloc(sizeof(Card) * returned_buff_size);
	if (tempCardBuffer == NULL) {
		perror("Fatal: Failed to allocate tempCardBuffer\n");
		exit(EXIT_FAILURE);
	}


	

	//BUG, TODO, Prevent just telling it a higher card number then you have
	for (int i = 0; i < returned_buff_size; i++) {

		if (buff[i] > currPlayerDeckSize) {
			//Illegal, cannot access cards not in your hand
			fprintf(stderr, "Illegal hand access\n");
			continue; 
			//We're gonna have an uninitalized space in tempCardBuffer,
			// Free TCB, and fail playCards?, or call 
		}

		tempCardBuffer[i] = (Card) {getCurrentPlayer(Game)->hand[buff[i]].suit, getCurrentPlayer(Game)->hand[buff[i]].number};
	}



	printf("%s\n", isMeld(tempCardBuffer, returned_buff_size) ? "Is Meld" : "Is Not Meld");

	// printf("RBS: %d\n", returned_buff_size);
	// for (int i = 0; i < returned_buff_size; i++) {
	// 	pCard(tempCardBuffer[i]);
	// }


	if (isMeld(tempCardBuffer, returned_buff_size)) {
		//We play the cards
		//TODO, sainity Logic
		//TODO, remove cards from deck
		//TODO, need deck function to remove card from middle of deck, and defrag the deck

		int indexofApp;
		for (int i = 0; i < returned_buff_size; i++) {
			
			indexofApp = deckPush(getCurrentPlayer(Game)->inPlay, DECK_SIZE, tempCardBuffer[i]);

			//Add Cards To Run
			getCurrentPlayer(Game)->ipRuns[getCurrentPlayer(Game)->amountRuns].runCards[i] = \
			(CardIndex) {tempCardBuffer[i], indexofApp};

			getCurrentPlayer(Game)->ipRuns[getCurrentPlayer(Game)->amountRuns].size++;

			//When in order e.g. (0 .. 2), causes the last item to be repeated into `inPlay` instead of being removed from
			// `hand`
			

		}
		getCurrentPlayer(Game)->amountRuns++;

		//FREE THIS
		int *tempiBuff = (int*) malloc(sizeof(int) * returned_buff_size);
		if (tempiBuff == NULL) {
			//Failed to allocate
			perror("Failed to allocate tempiBuff\n");
			#ifndef DEBUG
			exit(EXIT_FAILURE);
			#endif
		}

		memcpy(tempiBuff, buff, sizeof(int) * returned_buff_size);
		qsort(tempiBuff, returned_buff_size, sizeof(int), comparInt);

		#ifdef DEBUG
		printf("tempibuf:\n");
		for (int i = 0; i < returned_buff_size; i++) {
			printf("\t%d\n", tempiBuff[i]);
		}
		#endif

		
		for (int i = returned_buff_size - 1; i >= 0; i--) {
			//Each time we remove one, we need to (do something with the diffrence between buff[i] - buff[i - 1])
			#ifdef DEBUG
			printf("Removing %d, i%d ", buff[i], i);
			#endif
			deckRemoveMiddle(getCurrentPlayer(Game)->hand, DECK_SIZE, buff[i]);
		}

		free(tempiBuff);


	} else {
		//Player tried to play cards that are not a meld, return them to getCardNumbers
		printf("The cards selected are not a meld\n");
		goto askForCardNumbers;
	}

	printf("\n\n");

	free(tempCardBuffer);
	return;
}



void process_turn(gState* Game) {

	//Play cards or end turn (blank char?)

	//printf("\n");

	//Make sure the user knows their most current hand
	printf("\n----------\nYour hand:\n");
	dumpHand(getCurrentPlayer(Game)->hand, true);
	printf("\n");

	
	char c;
	do {
		printf("(P)lay cards or (S)kip\n");
		scanf(" %c", &c);
		flushKeyboard();
	} while (c != 'P' && c != 'p' && c != 'S' && c != 's');
	

	if(c == 'P' || c =='p') {
		playCards(Game);
	}

	// switch (c) {
	// 	case 'P':
	// 	case 'p':
	// 		//case
	// 		playCards(Game);

	// 		break;
	// 	case 'S':
	// 	case 's':
	// 		//We want to skip turn, just return
	// 		// printf("Deck:\n");
	// 		// dumpDeck(Game.Deck);

	// 		// printf("\nDiscard:\n");
	// 		// dumpDeck(Game.Discard);

	// 		// printf("\nP1:\n");
	// 		// dumpDeck(Game.Player.hand);

	// 		// printf("\nP1 IP:\n");
	// 		// dumpDeck(Game.Player.inPlay);

	// 		// printf("\nP2:\n");
	// 		// dumpDeck(Game.Computer.hand);

	// 		// printf("\nP2 IP:\n");
	// 		// dumpDeck(Game.Computer.inPlay);

	// 		// printf("\n\n");
	// 		return;
	// }


	return;
}


void end_turn(gState* Game) {

	//Need to discard

	//Going to do this shitally, refactor later


	printf("Your hand:\n");
	dumpHand(getCurrentPlayer(Game)->hand, true);

	printf("Discard Pile:\n");
	dumpHand(Game->Discard, true);


	printf("Discard Card Number: ");
	int selected;
	int NOC;

	do {
		NOC = scanf("%d", &selected);
		flushKeyboard();
	} while (NOC != 1);

	//Probably need to sanity check this, and check boundrys
	//Definetly need to boundry and sainty check this
	deckPush(Game->Discard, DECK_SIZE, getCurrentPlayer(Game)->hand[selected]);
	deckRemoveMiddle(getCurrentPlayer(Game)->hand, DECK_SIZE, selected);



	//need to check when someone discards their last card, thus ending the game


	printf("\n\n");
	return;
}




void pCard(Card c) {
	printf("(%c%c)", numChar(c.number), suitChar(c.suit));
	return;
}


