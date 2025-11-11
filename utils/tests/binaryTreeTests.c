#include "../include/binaryTree.h"
#include "../include/random.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int numTests = 100;

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

bool testBSTProperty(BinaryTree_t *tree) {
  BTNode_t **nodes = malloc(sizeof(BTNode_t *) * (tree->maxDepth + 1));
  if (nodes == NULL) {
    printf("Could not allocate memory for tree with length %d", tree->maxDepth);
    return false;
  }

  nodes[0] = tree->head;
  int i = 0;
  while (i > -1) {
    BTNode_t *node = nodes[i];
    int l = node->left != NULL;
    int r = node->right != NULL;
    if (l) {
      int comparison = tree->compare_func(node->left->value, node->value);
      if (!(comparison < 0)) {
        return false;
      }
      nodes[i] = node->left;
    }
    if (r && l) {
      i++;
    }
    if (r) {
      int comparison = tree->compare_func(node->right->value, node->value);
      if (comparison < 0) {
        return false;
      }
      nodes[i] = node->right;
    }
    if (!r && !l) {
      i--;
    }
  }

  free(nodes);

  return true;
}

void repr(BTNode_t *node, char *buffer, int bufferSize) {
  snprintf(buffer, bufferSize, "%d", *((int *)node->value));
}

void testBinaryTree() {
  for (int i = 1; i <= numTests; i++) {
    BinaryTree_t *tree = newBinaryTree(&compare);

    for (int j = 0; j < i * 10; j++) {
      int *item = malloc(sizeof(int));
      *item = randInt(-99, 99);
      BTNode_t *node = btInsert(tree, (void *)item);
      if (node == NULL) {
        printf("Could not create node\n");
        return;
      }
    }

    printTree(tree, repr, 4);

    bool passed = testBSTProperty(tree);
    if (!passed) {
      printf("Failed BST Property!\n");
    }
  }
  printf("✅ All tests passed!\n");
}

int main(int argc, char *argv[]) {
  testBinaryTree();
  return 0;
}
