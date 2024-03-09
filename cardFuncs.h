#pragma once

#include "types.h"

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <time.h>

#include <string.h>
#include <math.h>




bool isRun(Card cards[], int size);
int comparCard (const void* e1, const void* e2);

bool isSet(Card cards[], int size);
bool isMeld(Card cards[], int size);







