#include "../include/binaryTree.h"
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define min(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a < _b ? _a : _b;                                                         \
  })

// --- Public Function ---

/**
 * Creates a new Binary Tree.
 * @param capacity Initial number of items.
 * @param compare_func Function to compare items.
 * @return A pointer to the new BinaryTree, or NULL on failure.
 */
BinaryTree_t *newBinaryTree(int (*compare_func)(const void *item1,
                                                const void *item2)) {
  BinaryTree_t *tree = malloc(sizeof(BinaryTree_t));
  if (tree == NULL) {
    return NULL;
  }

  tree->maxDepth = -1;
  tree->length = 0;
  tree->compare_func = compare_func;
  tree->head = NULL;

  return tree;
}

BTNode_t *btInsert(BinaryTree_t *tree, void *item) {
  BTNode_t *newNode = malloc(sizeof(BTNode_t));
  if (newNode == NULL) {
    return NULL;
  }

  newNode->value = item;
  newNode->right = NULL;
  newNode->left = NULL;

  tree->length++;
  if (tree->head == NULL) {
    tree->head = newNode;
    tree->maxDepth = 0;
    return newNode;
  }

  int depth = 1;
  BTNode_t *current = tree->head;
  while (true) {
    int comparison = tree->compare_func(item, current->value);

    if (comparison < 0) {
      if (current->left == NULL) {
        current->left = newNode;
        if (depth > tree->maxDepth) {
          tree->maxDepth = depth;
        }
        return newNode;
      } else {
        current = current->left;
      }
    } else {
      if (current->right == NULL) {
        current->right = newNode;
        if (depth > tree->maxDepth) {
          tree->maxDepth = depth;
        }
        return newNode;
      } else {
        current = current->right;
      }
    }
    depth++;
  }
}

int btRemove(BinaryTree_t *tree, const void *item) {
  BTNode_t *current = tree->head;
  bool notFound = true;
  while (notFound) {
    int comparison = tree->compare_func(item, current->value);

    if (comparison < 0) {
      if (current->left == NULL) {
        return -1;
      }
      current = current->left;
    } else if (comparison > 0) {
      if (current->right == NULL) {
        return -1;
      }
      current = current->right;
    } else {
      notFound = false;
    }
  }

  if (current->left == NULL && current->right == NULL) {
    free(current);
  } else if (current->right == NULL) {
    BTNode_t *moved = current->left;
    while (moved->left != NULL) {
      moved = moved->left;
    }
    current->value = moved->value;
    free(moved);
  } else {
    BTNode_t *moved = current->right;
    while (moved->right != NULL) {
      moved = moved->right;
    }
    current->value = moved->value;
    free(moved);
  }
  return 0;
}

// TODO: decrease length
int btRemoveWithValue(BinaryTree_t *tree, const void *item) {
  BTNode_t *current = tree->head;
  bool notFound = true;
  while (notFound) {
    int comparison = tree->compare_func(item, current->value);

    if (comparison < 0) {
      if (current->left == NULL) {
        return -1;
      }
      current = current->left;
    } else if (comparison > 0) {
      if (current->right == NULL) {
        return -1;
      }
      current = current->right;
    } else {
      notFound = false;
    }
  }

  if (current->left == NULL && current->right == NULL) {
    free(current->value);
    free(current);
  } else if (current->right == NULL) {
    BTNode_t *moved = current->left;
    while (moved->left != NULL) {
      moved = moved->left;
    }
    current->value = moved->value;
    free(moved->value);
    free(moved);
  } else {
    BTNode_t *moved = current->right;
    while (moved->right != NULL) {
      moved = moved->right;
    }
    current->value = moved->value;
    free(moved->value);
    free(moved);
  }
  return 0;
}

void btDestroy(BinaryTree_t *tree) {
  BTNode_t *stack[(int)log2(tree->length)];

  stack[0] = tree->head;
  int idx = 0;

  while (idx > -1) {
    if (stack[idx]->left != NULL) {
      stack[idx + 1] = stack[idx]->left;
      idx++;
    } else if (stack[idx]->right != NULL) {
      stack[idx + 1] = stack[idx]->right;
      idx++;
    } else {
      free(stack[idx]);
      idx--;
    }
  }
  free(tree);
}

void btDestroyWithValues(BinaryTree_t *tree) {
  BTNode_t *stack[(int)log2(tree->length)];

  stack[0] = tree->head;
  int idx = 0;

  while (idx > -1) {
    if (stack[idx]->left != NULL) {
      stack[idx + 1] = stack[idx]->left;
      idx++;
    } else if (stack[idx]->right != NULL) {
      stack[idx + 1] = stack[idx]->right;
      idx++;
    } else {
      free(stack[idx]->value);
      free(stack[idx]);
      idx--;
    }
  }
  free(tree);
}

void printTree(BinaryTree_t *tree,
               void (*repr)(BTNode_t *node, char *buffer, int bufferSize),
               int bufferSize) {

  if (tree->head == NULL) {
    printf("Empty tree\n");
    return;
  }
  if (tree->maxDepth > 6) {
    printf("Tree too big to print\n");
    return;
  }

  BTNode_t **nodes = calloc(pow(2, tree->maxDepth + 1) - 1, sizeof(BTNode_t *));
  nodes[0] = tree->head;

  int i = 0, j = 1, ctr = 1;
  while (ctr < tree->length) {
    if (nodes[i] != NULL) {
      if (nodes[i]->left != NULL) {
        nodes[j] = nodes[i]->left;
        ctr++;
      }
      j++;
      if (nodes[i]->right != NULL) {
        nodes[j] = nodes[i]->right;
        ctr++;
      }
    } else {
      j++;
    }
    j++;
    i++;
  }

  char *buffer = malloc(sizeof(char) * bufferSize);
  int maxSpace = pow(2, tree->maxDepth) * bufferSize;
  int start = 0, end = 1;
  int depth = 1;
  int nSep = maxSpace / 2, cSep = maxSpace / 4;
  ctr = 0;
  while (ctr < tree->length) {
    // printf("(%d, %d, %d)", start, end, ctr);
    // Print nodes:
    for (int i = start; i < end; i++) {
      if (nodes[i] != NULL) {
        ctr++;
        repr(nodes[i], buffer, bufferSize);
        printf("%*s", nSep, buffer);
        printf("%*s", nSep, "");
        if (ctr == tree->length) {
          printf("\n");
          free(buffer);
          free(nodes);
          return;
        }
      } else {
        printf("%*s", nSep * 2, "");
      }
    }
    printf("\n%*s", cSep, "");

    // Print node connections
    for (int i = start; i < end; i++) {
      if (nodes[i] != NULL) {
        if (nodes[i]->left != NULL) {
          for (int j = 0; j < cSep - 1; j++) {
            printf("_");
          }
          printf("/");
        } else {
          printf("%*s", cSep, "");
        }
        if (nodes[i]->right != NULL) {
          printf("\\");
          for (int j = 0; j < cSep - 1; j++) {
            printf("_");
          }
        } else {
          printf("%*s", cSep, "");
        }
        printf("%*s", cSep * 2, "");
      } else {
        printf("%*s", cSep * 4, "");
      }
    }
    printf("\n");

    start = end;
    end = end * 2 + 1;
    depth++;

    nSep = maxSpace / ((int)pow(2, depth));
    cSep = maxSpace / ((int)pow(2, depth + 1));
  }
}
