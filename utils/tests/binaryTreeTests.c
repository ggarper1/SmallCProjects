#include "../include/binaryTree.h"
#include "../include/random.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int numTests = 1000;

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

void repr(BTNode_t *node, char *buffer, int bufferSize) {
  snprintf(buffer, bufferSize, "%d", *((int *)node->value));
}

BinaryTree_t *createTree(int size, void ***items) {
  BinaryTree_t *tree = newBinaryTree(&compare);
  *items = malloc(sizeof(void *) * size);

  if (tree == NULL) {
    return NULL;
  }

  for (int i = 0; i < size; i++) {
    int *item = malloc(sizeof(int));
    *item = randInt(-99, 99);
    (*items)[i] = item;
    BTNode_t *node = btInsert(tree, (void *)item);
    if (node == NULL) {
      return NULL;
    }
  }

  return tree;
}

bool testFind(BinaryTree_t *tree, void **items, int size) {
  for (int i = 0; i < size; i++) {
    BTNode_t *node = btFind(tree, items[i]);
    if (node == NULL || *(int *)(node->value) != *(int *)(items[i])) {
      printf("Items: %d", *(int *)items[0]);
      for (int j = 1; j < size; j++) {
        printf(", %d", *(int *)items[j]);
      }
      printf("\n");

      if (node == NULL) {
        printf("Element %d was not found when it should have.\n",
               *(int *)items[i]);
      } else {

        printf("Node value returned (%d) does not match value being searched "
               "for (%d).\n",
               *(int *)node->value, *(int *)items[i]);
      }
      return false;
    }
  }
  return true;
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

bool testInsert(BinaryTree_t *tree) {
  for (int i = 0; i < 50; i++) {
    int *item = malloc(sizeof(int));
    *item = randInt(-99, 99);
    BTNode_t *node = btInsert(tree, (void *)item);
    if (node == NULL || *((int *)node->value) != *item) {
      if (node == NULL) {
        printf("Tried to insert value %d yet NULL node was returned.\n", *item);
      } else {
        printf(
            "Tried to insert value %d yet node with value %d was returned.\n",
            *item, *((int *)node->value));
      }
      return false;
    }
  }
  return true;
}

bool testRemove(BinaryTree_t *tree, void **items, int size) {
  for (int i = 0; i < size / 2; i++) {
    void *value = btRemove(tree, items[i]);
    if (value == NULL || *((int *)value) != *((int *)items[i])) {
      if (value == NULL) {
        printf("Tried to remove value %d (which should be in the tree) yet "
               "NULL was returned.\n",
               *((int *)items[i]));
      } else {
        printf("Value removed (%d) is not the one expected (%d).\n",
               *((int *)value), *((int *)items[i]));
      }
      return false;
    }
  }

  for (int i = 0; i < 20; i++) {
    int *item = malloc(sizeof(int));
    *item = randInt(-99, 99);
    BTNode_t *node = btInsert(tree, (void *)item);
    void *value = btRemove(tree, (void *)item);
    if (value == NULL || *((int *)value) != *((int *)item)) {
      if (value == NULL) {
        printf("Tried to remove value %d (which should be in the tree) yet "
               "NULL was returned.\n",
               *((int *)item));
      } else {
        printf("Value removed (%d) is not the one expected (%d).\n",
               *((int *)value), *((int *)item));
      }
      return false;
    }
  }
  return true;
}

bool testDestroy(BinaryTree_t *tree) {
  btDestroy(tree);
  return true;
}

bool testDestroyAll(BinaryTree_t *tree) {
  btDestroyAll(tree);
  return true;
}

void testBinaryTree() {
  for (int i = 1; i <= numTests; i++) {
    void **items;
    int size = i * 10;
    BinaryTree_t *tree = createTree(size, &items);
    if (tree == NULL) {
      printf("🚨 Error creating tree\n");
      return;
    }

    if (i < 2) {
      printTree(tree, repr, 4);
    }

    if (!testBSTProperty(tree)) {
      printf("🚨 Failed BST Property!\n");
      return;
    }
    if (!testFind(tree, items, size)) {
      printf("🚨 Failed Find Test!\n");
      return;
    }
    if (!testInsert(tree)) {
      printf("🚨 Failed Insert Test!\n");
      return;
    }
    if (!testBSTProperty(tree)) {
      printf("🚨 Failed BST Property after insert!\n");
      return;
    }
    if (!testRemove(tree, items, size)) {
      printf("🚨 Failed Remove Test!\n");
      return;
    }
    if (!testBSTProperty(tree)) {
      printf("🚨 Failed BST Property after removal!\n");
      return;
    }
    if (i % 2 == 0) {
      testDestroy(tree);
      for (int j = 0; j < size; j++) {
        free(items[i]);
      }
    } else {
      testDestroyAll(tree);
    }
    free(items);
  }
  printf("✅ All tests passed!\n");
}

int main(int argc, char *argv[]) {
  testBinaryTree();
  return 0;
}
