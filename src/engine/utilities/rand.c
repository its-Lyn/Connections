#include "engine/utilities/rand.h"

#include <math.h>
#include <stdlib.h>

float rand_float(float min, float max) {
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}

float rand_int(int min, int max) {
	return rand() % (max - min) + 1 + min;
}
