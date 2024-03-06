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


typedef enum suit {
	JOKER = 0, CLUBS, HEARTS, SPADES, DIAMONDS
	//Even = Red, Odd = Black; JOKER is kinda like null card
} Suit;

typedef struct card {
	Suit suit;
	int number; //A = 1 & 14, 10 = T, 11 = J, 12 = Q, 13 = K
} Card;




void genDeck(Card[]);
void shuffle(Card deck[], int size);

char suitChar(Suit s);
char numChar(int cn);

void dumpDeck(Card deck[]);
void pCard(Card c);

void dealHand(Card deck[], Card hand1[], Card hand2[]);
Card deckPop(Card deck[], int size);

void dumpHand(Card hand[], bool newLine);
//void getUserCommand(void);
void getUserCommand(Card deck[], Card discard[], Card p1[], Card p2[]);

bool deckPush(Card deck[], int size, Card cd);

void discardCardAction(void);
void placeCardAction(void);

void printUsage(void);
void pickupCardAction(void);


const char TEN = 'T';
const char JACK = 'J';
const char QUEEN = 'Q';
const char KING = 'K';
const char ACE = 'A';
const Card BCARD = {JOKER, 0};


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
	Card Player[52] = {JOKER, 0};
	Card inPlay_Player[52] = {JOKER, 0};

	Card Computer[52] = {JOKER, 0};
	Card inPlay_Computer[52] = {JOKER, 0};

	
	//Dealing alternates tho...
	dealHand(deck, Player, Computer);

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
		dumpHand(Player, true);

		printf("Discard Pile:\n");
		dumpHand(discard, true);

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


void getUserCommand(Card deck[], Card discard[], Card p1[], Card p2[]) {

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
		dumpDeck(p1);

		printf("\nP2:\n");
		dumpDeck(p2);
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


bool deckPush(Card deck[], int size, Card cd) {
	//Returns true if it was able to append
	//
	//TODO FIX

	//Hopfully this works lmao

	for(int i = size - 1; i > 0; i--) {
		if(
			deck[i].suit != JOKER &&
			deck[i].number != 0
		) {
			if(i != size - 1) {
				deck[i + 1] = cd;
				return true;
			} else {
				//printf("i %d\n", i);
				return false;
			}
		}
	}
	//printf("???\n");
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







void pCard(Card c) {
	printf("(%c%c)", numChar(c.number), suitChar(c.suit));
	return;
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


char numChar(int cn) {
	if (cn >= 2 && cn < 10) {
		return cn + '0';
	}

	switch(cn) {
		case 0:
		return '0';

		case 1:
		return ACE;

		case 10:
		return TEN;
		
		case 11:
		return JACK;

		case 12:
		return QUEEN;

		case 13:
		return KING;
	}
}

char suitChar(Suit s) {
	switch(s) {
		case CLUBS:
		return 'C';

		case HEARTS:
		return 'H';

		case SPADES:
		return 'S';

		case DIAMONDS:
		return 'D';

		case JOKER:
		return '*';

		default:
		return '-';
	}
}


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






// void serverSpinUp() {

//     // https://www.youtube.com/watch?v=U28svzb1WUs

//     int domain = AF_INET;
//     int type = SOCK_STREAM;

//     int sock = socket(domain, type, 0);

//     if (sock < 0) {
//         perror("Failed to open socket");
//         exit(-1);
//     }
//     printf("Opened socket %d\n", sock);







//     return;
// }