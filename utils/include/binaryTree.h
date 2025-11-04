#include <stddef.h>

#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef struct Node {
  void *value;
  struct Node *right;
  struct Node *left;
} Node;

typedef struct BinaryTree {
  size_t length;
} BinaryTree;

// --- Public Function Prototypes ---

/**
 * Creates a new Binary Tree.
 * @param capacity Initial number of items.
 * @param compare_func Function to compare items.
 * @return A pointer to the new BinaryTree, or NULL on failure.
 */
BinaryTree *newBinaryTree(int (*compare_func)(const void *item1,
                                              const void *item2));

/**
 * Inserts a item in the Binary Tree.
 * Pointers to the item are stored (caller manages memory).
 * @param tree The Binary Tree.
 * @param item The item to insert.
 * @return NULL on failure or a pointe to the new node.
 */
int btInsert(BinaryTree *tree, void *item);

/**
 * Removes a item pair from the Binary Tree.
 * @param tree The hash table.
 * @param item The item to remove.
 * @return 0 on success (item removed), -1 if not found.
 */
int btRemove(BinaryTree *ht, const void *value);

/**
 * Destroys the hash table and frees all allocated memory.
 * @param tree The BinaryTree to destroy.
 */
void btDestroy(BinaryTree *tree);

/**
 * Destroys the Binary Tree and along with all the keys and values in it.
 * @param tree The Binary Tree to destroy.
 */
void btDestroyWithValues(BinaryTree *tree);

#endif
