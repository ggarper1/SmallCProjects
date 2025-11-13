#include "../include/random.h"
#include <stdlib.h>

int randInt(int min, int max) {
  int range = max - min + 1;
  return (rand() % range) + min;
}
