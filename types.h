#pragma once

#define DECK_SIZE 52


typedef enum suit {
	JOKER = 0, CLUBS, HEARTS, SPADES, DIAMONDS
	//Even = Red, Odd = Black; JOKER is kinda like null card
} Suit;

typedef struct card {
	Suit suit;
	int number; //A = 1 & 14, 10 = T, 11 = J, 12 = Q, 13 = K
} Card;

typedef enum courtCards {
    TEN = 'T', JACK = 'J', QUEEN = 'Q', KING = 'K', ACE = 'A'
} Court;

typedef struct playerState {
	Card* hand; //The players hand
	Card* inPlay; //Cards the player has in play
	//char name[10];
} pState;

typedef enum whoGoesMutex {
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


pState getCurrentPlayer(gState Game);

char suitChar(Suit s);
char numChar(int cn);


