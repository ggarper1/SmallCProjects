#include "../include/queue.h"
#include "../include/random.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int numTests = 3;

void repr(void *value, char *buffer, int bufferSize) {
  snprintf(buffer, bufferSize, "%d", *((int *)value));
}

bool testPeekAddRemoveDestroyAll(Queue_t *queue, int size) {
  int **items = malloc(size * sizeof(int *));

  for (int i = 0; i < size; i++) {
    if (qLength(queue) != i) {
      printf("🚨 Incorrect length\n");
      return false;
    }
    int *item = malloc(sizeof(int));
    *item = randInt(0, 99);
    items[i] = item;
    qAdd(queue, item);
  }

  for (int i = 0; i < size; i++) {
    if (qLength(queue) != size - i) {
      printf("🚨 Incorrect length\n");
      return false;
    }
    int *peeked = qPeek(queue);
    int *removed = qRemove(queue);
    if (*peeked != *items[i]) {
      printf("🚨 Peeked is incorrect");
      return false;
    }
    if (*removed != *items[i]) {
      printf("🚨 Peeked is incorrect");
      return false;
    }
    free(removed);
  }

  if (qLength(queue) != 0) {
    printf("🚨 Length should be 0\n");
    return false;
  }

  int *peeked = qPeek(queue);
  if (peeked != NULL) {
    printf("🚨 Peeked should be null");
    return false;
  }
  int *removed = qRemove(queue);
  if (removed != NULL) {
    printf("🚨 Peeked should be null");
    return false;
  }

  for (int i = 0; i < size / 10; i++) {
    int *item = malloc(sizeof(int));
    *item = randInt(0, 99);
    items[i] = item;
    qAdd(queue, item);
  }

  qDestroyAll(queue);

  free(items);
  return true;
}

bool testDestroy(Queue_t *queue) {
  int **items = malloc(sizeof(int) * 50);
  for (int i = 0; i < 50; i++) {
    int *item = malloc(sizeof(int));
    *item = randInt(0, 99);
    qAdd(queue, item);
    items[i] = item;
  }

  qDestroy(queue);
  for (int i = 0; i < 50; i++) {
    free(items[i]);
  }
  free(items);
  return true;
}

void testQueue() {
  for (int i = 1; i <= numTests; i++) {
    int size = i * 10;
    Queue_t *queue = newQueue(2);
    if (queue == NULL) {
      printf("🚨 Error creating tree\n");
      return;
    }

    if (i % 10 != 0) {
      if (!testPeekAddRemoveDestroyAll(queue, size * 2)) {
        printf("🚨 Failed Peek Add Remove Test!\n");
        return;
      }
    } else {
      testDestroy(queue);
    }
  }
  printf("✅ All tests passed!\n");
}

int main(int argc, char *argv[]) {
  testQueue();
  return 0;
}
