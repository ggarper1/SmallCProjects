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

BinaryTree_t *newBinaryTree(int (*compare_func)(const void *item1,
                                                const void *item2)) {
  BinaryTree_t *tree = malloc(sizeof(BinaryTree_t));
  if (tree == NULL) {
    return NULL;
  }

  tree->height = -1;
  tree->length = 0;
  tree->compare_func = compare_func;
  tree->root = NULL;

  return tree;
}

BTNode_t *btFind(BinaryTree_t *tree, void *item) {
  BTNode_t *current = tree->root;

  while (current != NULL) {
    int comparison = tree->compare_func(item, current->value);
    if (comparison < 0) {
      current = current->left;
    } else if (comparison > 0) {
      current = current->right;
    } else {
      return current;
    }
  }
  return NULL;
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
  if (tree->root == NULL) {
    tree->root = newNode;
    tree->height = 0;
    return newNode;
  }

  int depth = 1;
  BTNode_t *current = tree->root;
  while (true) {
    int comparison = tree->compare_func(item, current->value);

    if (comparison < 0) {
      if (current->left == NULL) {
        current->left = newNode;
        if (depth > tree->height) {
          tree->height = depth;
        }
        return newNode;
      } else {
        current = current->left;
      }
    } else {
      if (current->right == NULL) {
        current->right = newNode;
        if (depth > tree->height) {
          tree->height = depth;
        }
        return newNode;
      } else {
        current = current->right;
      }
    }
    depth++;
  }
}

void *btRemove(BinaryTree_t *tree, const void *item) {
  BTNode_t *current = tree->root;
  BTNode_t **prev = NULL;

  while (true) {
    int comparison = tree->compare_func(item, current->value);

    if (comparison < 0) {
      if (current->left == NULL) {
        return NULL;
      }
      prev = &current->left;
      current = current->left;
    } else if (comparison > 0) {
      if (current->right == NULL) {
        return NULL;
      }
      prev = &current->right;
      current = current->right;
    } else {
      break;
    }
  }

  tree->length--;

  if (current->left == NULL && current->right == NULL) {
    void *ptr = current->value;
    *prev = NULL;
    free(current);
    return ptr;
  } else if (current->right == NULL) {
    void *ptr = current->value;
    BTNode_t *toDelete = current->left;
    current->value = toDelete->value;
    current->left = toDelete->left;
    current->right = toDelete->right;

    free(toDelete);
    return ptr;
  } else if (current->left == NULL) {
    void *ptr = current->value;
    BTNode_t *toDelete = current->right;
    current->value = toDelete->value;
    current->left = toDelete->left;
    current->right = toDelete->right;

    free(toDelete);
    return ptr;
  } else {
    BTNode_t *toDelete = current->right;
    BTNode_t **prev = &(current->right);
    while (toDelete->left != NULL) {
      prev = &(toDelete->left);
      toDelete = toDelete->left;
    }
    if (toDelete->right != NULL) {
      *prev = toDelete->right;
    } else {
      *prev = NULL;
    }
    void *ptr = current->value;
    current->value = toDelete->value;

    free(toDelete);
    return ptr;
  }
}

void btDestroy(BinaryTree_t *tree) {
  if (tree->root == NULL) {
    free(tree);
    return;
  }

  BTNode_t **nodes = malloc(sizeof(BTNode_t *) * (tree->height + 1));
  nodes[0] = tree->root;
  int i = 0;

  while (i > -1) {
    BTNode_t *l = nodes[i]->left;
    BTNode_t *r = nodes[i]->right;
    free(nodes[i]);
    if (l != NULL) {
      nodes[i] = l;
    }
    if (r && l) {
      i++;
    }
    if (r != NULL) {
      nodes[i] = r;
    }
    if (!r && !l) {
      i--;
    }
  }
  free(nodes);
  free(tree);
}

void btDestroyAll(BinaryTree_t *tree) {
  if (tree->root == NULL) {
    free(tree);
    return;
  }

  BTNode_t **nodes = malloc(sizeof(BTNode_t *) * (tree->height + 1));
  nodes[0] = tree->root;

  int i = 0;
  while (i > -1) {
    BTNode_t *l = nodes[i]->left;
    BTNode_t *r = nodes[i]->right;
    free(nodes[i]->value);
    free(nodes[i]);
    if (l != NULL) {
      nodes[i] = l;
    }

    if (r && l) {
      i++;
    }
    if (r != NULL) {
      nodes[i] = r;
    }
    if (!r && !l) {
      i--;
    }
  }

  free(nodes);
  free(tree);
}

void printTree(BinaryTree_t *tree,
               void (*repr)(BTNode_t *node, char *buffer, int bufferSize),
               int bufferSize) {

  if (tree->root == NULL) {
    printf("Empty tree\n");
    return;
  }
  if (tree->height > 6) {
    printf("Tree too big to print\n");
    return;
  }

  BTNode_t **nodes = calloc(pow(2, tree->height + 1) - 1, sizeof(BTNode_t *));
  nodes[0] = tree->root;

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
  int maxSpace = pow(2, tree->height) * bufferSize;
  int start = 0, end = 1;
  int depth = 1;
  int nSep = maxSpace / 2, cSep = maxSpace / 4;
  ctr = 0;
  while (ctr < tree->length) {
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
