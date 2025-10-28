#include "print.h"
#include <stdbool.h>
#include <stdio.h>

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
