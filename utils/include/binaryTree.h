#include <stddef.h>
#include <stdio.h>

#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef struct BTNode {
  void *value;
  struct BTNode *right;
  struct BTNode *left;
} BTNode_t;

typedef struct BinaryTree {
  size_t length;
  int maxDepth;
  BTNode_t *head;
  int (*compare_func)(const void *item1, const void *item2);
} BinaryTree_t;

// --- Public Function Prototypes ---

/**
 * Creates a new Binary Tree.
 * @param capacity Initial number of items.
 * @param compare_func Function to compare items.
 * @return A pointer to the new BinaryTree, or NULL on failure.
 */
BinaryTree_t *newBinaryTree(int (*compare_func)(const void *item1,
                                                const void *item2));

/**
 * Inserts a item in the Binary Tree.
 * Pointers to the item are stored (caller manages memory).
 * @param tree The Binary Tree.
 * @param item The item to insert.
 * @return NULL on failure or a pointe to the new node.
 */
BTNode_t *btInsert(BinaryTree_t *tree, void *item);

/**
 * Removes a item pair from the Binary Tree.
 * @param tree The hash table.
 * @param item The item to remove.
 * @return 0 on success (item removed), -1 if not found.
 */
int btRemove(BinaryTree_t *ht, const void *value);

/**
 * Destroys the hash table and frees all allocated memory.
 * @param tree The BinaryTree to destroy.
 */
void btDestroy(BinaryTree_t *tree);

/**
 * Destroys the Binary Tree and along with all the keys and values in it.
 * @param tree The Binary Tree to destroy.
 */
void btDestroyWithValues(BinaryTree_t *tree);

/**
 * Prints the Binary Tree.
 * @param tree The Binary Tree to print.
 */
void printTree(BinaryTree_t *tree,
               void (*repr)(BTNode_t *node, char *buffer, int bufferSize),
               int nodeReprBuffer);

#endif
