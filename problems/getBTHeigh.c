#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/include/binaryTree.h"
#include "../utils/include/random.h"

#define max(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })

// Recursive solution
int getHeightRec(BTNode_t *root) {
  if (root == NULL) {
    return -1;
  }
  return 1 + max(getHeightRec(root->left), getHeightRec(root->right));
}

// Iterative solution
int getHeightIt(BTNode_t *root) {
  // TODO: Implement
  return 0;
}

int compare(const void *item1, const void *item2) {
  const int *a = (const int *)item1;
  const int *b = (const int *)item2;

  if (*a < *b) {
    return -1;
  } else if (*b < *a) {
    return 1;
  } else {
    return 0;
  }
}

int main(void) {
  BinaryTree_t *tree = newBinaryTree(compare);
  for (int i = 0; i < 100; i++) {
    int *item = malloc(sizeof(int));
    *item = randInt(0, 200);
    btInsert(tree, item);
  }

  printf("%d == %d\n", getHeightIt(tree->root), tree->height);
  return 0;

  int recFail = getHeightRec(tree->root) != tree->height;
  if (recFail) {
    printf("🚨 Recursive height id Failing\n");
  }

  int itFail = getHeightIt(tree->root) != tree->height;
  if (itFail) {
    printf("🚨 Iterative height id Failing\n");
  }
  if (!recFail && !itFail) {
    printf("✅ Tests passed!\n");
  }
  return 0;
}
