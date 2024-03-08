#pragma once





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
} pState;



char suitChar(Suit s);
char numChar(int cn);


