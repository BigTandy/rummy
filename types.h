#pragma once

#define DECK_SIZE 52

//#define DEBUG


typedef enum suit {
	JOKER = 0, CLUBS, HEARTS, SPADES, DIAMONDS
	//Even = Red, Odd = Black; JOKER is kinda like null card
} Suit;

typedef struct card {
	Suit suit;
	int number; //A = 1 & 14, 10 = T, 11 = J, 12 = Q, 13 = K
} Card;

typedef struct cardIndex {
	Card card;
	int index;
} CardIndex;

//Each card in a deck is unique
typedef struct run {
	//Card runCards[DECK_SIZE];
	CardIndex runCards[DECK_SIZE];
	int size;
} Run;

typedef enum courtCards {
    TEN = 'T', JACK = 'J', QUEEN = 'Q', KING = 'K', ACE = 'A'
} Court;

typedef struct playerState {
	Card* hand; //The players hand
	Card* inPlay; //Cards the player has in play
	int amountRuns;
	Run ipRuns[DECK_SIZE]; //Can prob optimize this later
	//char name[10];
} pState;

typedef enum whoGoesState {
	PLAYER,
	COMPUTER
} whoInPlay;

typedef enum turnState {
	notStarted,
	inPlay,
	turnEnded,
	discarded
} tState;


/*
	Hopefully all of the game state,
	takes in two pState's, 1 for player, 2 for computer
	Takes two Card*'s, First for deck, second for discard
*/
typedef struct gameState {
	pState Player;
	pState Computer;

	Card* Deck;
	Card* Discard;

	whoInPlay Who;
	tState turnState;
} gState;


pState* getCurrentPlayer(gState* Game);
pState* getOtherPlayer(gState* Game);

char suitChar(Suit s);
char numChar(int cn);


