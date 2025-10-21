#include <stdbool.h>
#include <stdlib.h>

#ifndef UTILS_H
#define UTILS_H

// Random
int randInt(int min, int max);

// Math
int abs(int n);

// Sorts
int *qsortInt(int list[], size_t length);

// Prints
void printIntList(int *list, int length);
void printIntSeqMatrix(int *matrix, int rows, int cols);
void printBoolSeqMatrix(bool *matrix, int rows, int cols);

#endif
