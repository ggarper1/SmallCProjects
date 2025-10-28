#include "sort.h"
#include <stdlib.h>
#include <string.h>

// Sortes
int comapareInts(const void *a, const void *b) {
  const int *val_a = (const int *)a;
  const int *val_b = (const int *)b;

  int num_a = *val_a;
  int num_b = *val_b;

  if (num_a < num_b) {
    return -1;
  } else if (num_a > num_b) {
    return 1;
  } else {
    return 0;
  }
}

int *qsortInt(int list[], size_t length) {
  int *sorted = malloc(length * sizeof(int));
  memcpy(sorted, list, length * sizeof(int));

  qsort(sorted, length, sizeof(int), comapareInts);

  return sorted;
}
