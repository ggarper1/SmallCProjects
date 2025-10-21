#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Random
int randInt(int min, int max) {
  int range = max - min + 1;
  return (rand() % range) + min;
}

// Math
int abs(int n) { return n > 0 ? n : -n; }

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

// Prints
void printIntList(int *list, int length) {
  printf("[");
  for (int i = 0; i < length - 1; i++) {
    printf("%d, ", list[i]);
  }
  printf("%d]\n", list[length - 1]);
}

void printIntSeqMatrix(int *matrix, int rows, int cols) {
  printf("[\n");
  for (int j = 0; j < rows; j++) {
    printf("\t%6d", matrix[j * cols]);

    for (int i = 0; i < cols; i++) {
      printf(", %6d", matrix[j * cols + i]);
    }
    printf("\n");
  }
  printf("]\n");
}

void printBoolSeqMatrix(bool *matrix, int rows, int cols) {
  printf("[\n");
  for (int j = 0; j < rows; j++) {
    printf("\t%s", matrix[j * cols] ? "T" : "F");
    for (int i = 1; i < cols; i++) {
      printf(", %s", matrix[j * cols + i] ? "T" : "F");
    }
    printf("\n");
  }
  printf("]\n");
}
