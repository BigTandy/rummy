#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <time.h>

#include <string.h>
#include <math.h> //https://stackoverflow.com/a/5248968

#include <termios.h>
#include <ctype.h>

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



// const char TEN = 'T';
// const char JACK = 'J';
// const char QUEEN = 'Q';
// const char KING = 'K';
// const char ACE = 'A';




extern __ssize_t getline(char **__restrict __lineptr, size_t *n, FILE *stream);


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
				start_turn(Game);
				Game.turnState = inPlay;
				break;
			case inPlay:
				//Ask and process game
				process_turn(Game);
				Game.turnState = turnEnded;
				break;
			case turnEnded:
				//End turn and discard
				end_turn(Game);
				//Need to switch player and tState
				break;
			case discarded:
				//Cleanup at turn end, and check if end-of-game
				
				break;


		}


	}



	return 0;
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

	

	//TODO, Print out hand after picking up a card!! <---

	char c;
	do {
		printf("Pickup from (D)eck or D(i)scard? ");
		scanf(" %c", &c);
	} while (c != 'D' && c != 'd' && c != 'I' && c != 'i');


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



void _DEP_getCardNumbers(int numArray[], int size) {
	//numArray is buffer to return numbers with
	//Return by refrence

	/*
	char *buffertest = NULL;
	size_t bufftestSize;
	int read = 0;
	read = getline(&buffertest, &bufftestSize, stdin);

	printf("Bytes: %zu, Return Code: %d\n", bufftestSize, read);
	printf("%s\n", buffertest);
	*/

	int b_idx = 0;



	printf("Num: ");

	do {
		
		//scanf("%d", &numArray[b_idx]);
		//fgets(&numArray[b_idx], 1, stdin);
		

		

		//tcflush(0, TCIFLUSH); //Flush keyboard buffer

		b_idx++;
		//printf("\n%c\n", temp);
	} while (numArray[b_idx - 1] >= 0 && b_idx < size);

	return;
}



void getCardNumbers(int** intArray, int* size) {
	/*
		User should free `intArray` after use
	*/

	char *buffer = NULL; //NEED TO FREE THIS WHEN WE'RE DONE
	size_t bytesRead = 0;
	int charsRead;

	printf("Cards to play: ");

	//tcflush(0, TCIFLUSH); //Flush keyboard buffer

	while(getchar() != '\n'); //Actually flush k_buffer

	charsRead = getline(&buffer, &bytesRead, stdin);

	if(charsRead < 0) {
		//Failed
		perror("Failed to read in? (getCardNumbers)\n");
	}

	//Grab ints using sscanf() in loop?

	// printf("Bytes: %zu, Return Code: %d\n", bytesRead, charsRead);
	// printf("Read: %s\n", buffer);

	#define def_intArr_size 120 //amount of ints not bytes

	*intArray = (int *) malloc(sizeof(int) * def_intArr_size);
	

	int hold;
	int idx = 0;
	int numsRead = 0;
	int LOC;
	
	while(
		(LOC = sscanf(buffer + idx, "%d", &hold)) > 0 && 
		(((sizeof(char) * idx) < bytesRead) && (idx < charsRead))) //Just make sure not to overrun the buffer
	{
		if(!isdigit(*(buffer + idx))) {
			//Current char is NOT a number, pass over it
			idx++;
			continue;
		}
		//printf("%d, %c, %d, L: %d\n", hold, *(buffer + idx), idx, LOC);

		idx += (int) floor(log10(hold)) + 1;
		numsRead++;
		//idx++; //Need to account for multidigit numberssssssss
	}


	// *intArray = (int *) malloc(sizeof(int) * numsRead);
	// *size = numsRead;

	// if(*intArray == NULL) {
	// 	//We failed...
	// 	perror("Failed to allocate intArray (getCardNumber)\n");
	// }


	// for(int i = 0; i < numsRead; i++) {
	// 	(*intArray)[i] = 
	// }




	DONE:
	free(buffer);
	return;
}



void playCards(gState Game) {

	//Left off here,
	// March 9th 2024 1:02 AM
	/*
		Need to get from the user what cards they want to play,
		if those form a meld (Play cards on other players aswell, todo) (play cards onto their own inPlay aswell, todo)
		and then actually play the cards into the players `currentPlayer().inPlay` deck
		return to process_turn (Actually jump back to the top, or restart question loop, so player can play multiple times)
	
	
	*/

	//Get cards numbers from user

	int buff[DECK_SIZE];  //Prob name this better
	
	for(int i = 0; i < DECK_SIZE; i++) {
		buff[i] = -2;
	}


	

	askForCardNumbers:
	getCardNumbers(buff, DECK_SIZE);

	int currPlayerDeckSize = deckSize(getCurrentPlayer(Game).hand);

	//Get size of returned card numbers

	//Make func?
	int returned_buff_size = 0;

	while (buff[returned_buff_size] >= 0) {
		returned_buff_size++;
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

		tempCardBuffer[i] = (Card) {getCurrentPlayer(Game).hand[buff[i]].suit, getCurrentPlayer(Game).hand[buff[i]].number};
	}

	printf("%s\n", isMeld(tempCardBuffer, returned_buff_size) ? "Is Meld" : "Is Not Meld");


	free(tempCardBuffer);
	return;
}



void process_turn(gState Game) {

	//Play cards or end turn (blank char?)

	//printf("\n");
	
	char c;
	do {
		printf("(P)lay cards or (S)kip\n");
		scanf(" %c", &c);
	} while (c != 'P' && c != 'p' && c != 'S' && c != 's');
	
	switch (c) {
		case 'P':
		case 'p':
			//case
			playCards(Game);

			break;
		case 'S':
		case 's':
			//We want to skip turn, just return
			// printf("Deck:\n");
			// dumpDeck(Game.Deck);

			// printf("\nDiscard:\n");
			// dumpDeck(Game.Discard);

			// printf("\nP1:\n");
			// dumpDeck(Game.Player.hand);

			// printf("\nP1 IP:\n");
			// dumpDeck(Game.Player.inPlay);

			// printf("\nP2:\n");
			// dumpDeck(Game.Computer.hand);

			// printf("\nP2 IP:\n");
			// dumpDeck(Game.Computer.inPlay);

			// printf("\n\n");
			return;
	}


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


