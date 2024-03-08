#include "types.h"







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






