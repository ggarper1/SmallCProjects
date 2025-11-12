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
int getHeightRec(BTNode_t *root, int depth) {
  int l = root->left == NULL;
  int r = root->right == NULL;
  if (l && r) {
    return depth;
  } else if (r) {
    return getHeightRec(root->left, depth + 1);
  } else if (l) {
    return getHeightRec(root->right, depth + 1);
  } else {
    int lDepth = getHeightRec(root->left, depth + 1);
    int rDepth = getHeightRec(root->right, depth + 1);
    if (lDepth > rDepth) {
      return lDepth;
    }
    return rDepth;
  }
}

int getHeight(BTNode_t *root) {
  if (root == NULL) {
    return -1;
  }
  return getHeightRec(root, 0);
}

// Iterative solution
int getHeightIt(BTNode_t *root) {
  if (root == NULL) {
    return 0;
  }
  int end = 0;
  size_t size = 8;
  BTNode_t **nodes = malloc(sizeof(BTNode_t *) * size);
  bool *path = calloc(size, sizeof(bool));

  int height = 0;
  BTNode_t *node = root;
  while (true) {
    while (nodes[end]->left != NULL && nodes[end]->right != NULL) {
      while (nodes[end]->left != NULL) {
        if (end == size) {
          BTNode_t **newNodes = malloc(2 * size * sizeof(BTNode_t *));
          memcpy(nodes, newNodes, size * sizeof(BTNode_t *));
          free(nodes);
          nodes = newNodes;
          size *= 2;
        }
        path[end] = 0;
        end++;
        nodes[end] = nodes[end - 1]->left;
      }
      height = max(height, end);
      if (end == size) {
        BTNode_t **newNodes = malloc(2 * size * sizeof(BTNode_t *));
        memcpy(nodes, newNodes, size * sizeof(BTNode_t *));
        free(nodes);
        nodes = newNodes;
        size *= 2;
      }

      if (nodes[end]->right != NULL) {
        path[end] = 1;
        end++;
        nodes[end] = nodes[end - 1]->right;
      }
      height = max(height, end);
    }
    while (path[end] == 0 && nodes[end]->right != NULL && end > 0) {
      end--;
    }
    if (end > 0) {
      path[end] = 1;
      end++;
      nodes[end] = nodes[end - 1]->right;
    } else {
      return height;
    }
  }
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
  int recFail = getHeight(tree->root) != tree->height;
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
