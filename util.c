#include "types.h"

#include <stdio.h>
#include <stdlib.h>

#include <math.h> //https://stackoverflow.com/a/5248968
#include <assert.h>

#include "util.h"





void getCardNumbers(int intArray[], int size) {
	
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


	// printf("Bytes: %zu, Return Code: %d\n", bytesRead, charsRead);
	// printf("Read: %s\n", buffer);


	int hold = -1;
	int idx = 0;
	int numsRead = 0;
	int LOC;
	
	while(
		(LOC = sscanf(buffer + idx, "%d", &hold)) > 0 && 
		(((sizeof(char) * idx) < bytesRead) && (idx < charsRead))) //Just make sure not to overrun the buffer
	{

        //assert(idx > 0);

		if(!isdigit(*(buffer + idx))) {
			//Current char is NOT a number, pass over it
			idx++;
			continue;
		}
		//printf("%d, %c, %d, L: %d\n", hold, *(buffer + idx), idx, LOC);

		if(size > numsRead) {
			intArray[numsRead] = hold;
		} else {
			fprintf(stderr, "Too much being written to intArray, oops\n");
			raise(SIGTRAP);
		}

        if (hold > 0) {
		    idx += (int) floor(log10(hold)) + 1;
        } else {
            idx++;
        }
		numsRead++;
		//idx++; //Need to account for multidigit numberssssssss
	}


	DONE:
	free(buffer);
	return;
}

