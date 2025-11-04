#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
  void *value;
  struct Node *right;
  struct Node *left;
} Node;

typedef struct BinaryTree {
  size_t length;
  Node *head;
  int (*compare_func)(const void *item1, const void *item2);
} BinaryTree;

// --- Public Function ---

/**
 * Creates a new Binary Tree.
 * @param capacity Initial number of items.
 * @param compare_func Function to compare items.
 * @return A pointer to the new BinaryTree, or NULL on failure.
 */
BinaryTree *newBinaryTree(int (*compare_func)(const void *item1,
                                              const void *item2)) {
  BinaryTree *tree = malloc(sizeof(BinaryTree));
  if (tree == NULL) {
    return NULL;
  }

  tree->length = 0;
  tree->compare_func;
  tree->head = NULL;

  return tree;
}

Node *btInsert(BinaryTree *tree, void *item) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    return NULL;
  }

  newNode->value = item;
  newNode->right = NULL;
  newNode->left = NULL;

  Node *current = tree->head;
  bool notAdded = true;
  while (notAdded) {
    int comparison = tree->compare_func(item, current->value);

    if (comparison < 0) {
      if (current->left == NULL) {
        current->left = newNode;
        notAdded = false;
      } else {
        current = current->left;
      }
    } else {
      if (current->right == NULL) {
        current->right = newNode;
        notAdded = false;
      } else {
        current = current->right;
      }
    }
  }

  return newNode;
}

int btRemove(BinaryTree *tree, const void *item) {
  Node *current = tree->head;
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
    Node *moved = current->left;
    while (moved->left != NULL) {
      moved = moved->left;
    }
    current->value = moved->value;
    free(moved);
  } else {
    Node *moved = current->right;
    while (moved->right != NULL) {
      moved = moved->right;
    }
    current->value = moved->value;
    free(moved);
  }
  return 0;
}

int btRemoveWithValue(BinaryTree *tree, const void *item) {
  Node *current = tree->head;
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
    Node *moved = current->left;
    while (moved->left != NULL) {
      moved = moved->left;
    }
    current->value = moved->value;
    free(moved->value);
    free(moved);
  } else {
    Node *moved = current->right;
    while (moved->right != NULL) {
      moved = moved->right;
    }
    current->value = moved->value;
    free(moved->value);
    free(moved);
  }
  return 0;
}

void btDestroy(BinaryTree *tree) {
  Node *stack[(int)log2(tree->length)];

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

void btDestroyWithValues(BinaryTree *tree) {
  Node *stack[(int)log2(tree->length)];

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
