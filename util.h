#pragma once

#include "types.h"

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <time.h>

#include <string.h>
#include <math.h> //https://stackoverflow.com/a/5248968

#include <termios.h>
#include <ctype.h>

#include <signal.h>



void flushKeyboard(void);
void getCardNumbers(int intArray[], int size);

