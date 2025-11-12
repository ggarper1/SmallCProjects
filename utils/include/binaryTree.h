#include <stdbool.h>
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
  int height;
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
 * Checks if a element is in the Binary Tree.
 * @param tree The binary Tree.
 * @param item Pointer to the item.
 * @return The node containing the element if it's in the tree, NULL otherwise.
 */
BTNode_t *btFind(BinaryTree_t *tree, void *item);

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
 * @return NULL if the element was not found or the pointer to the value if it
 * was found.
 */
void *btRemove(BinaryTree_t *ht, const void *value);

/**
 * Destroys the hash table and frees all allocated memory.
 * @param tree The BinaryTree to destroy.
 */
void btDestroy(BinaryTree_t *tree);

/**
 * Destroys the Binary Tree and along with all the values in it.
 * @param tree The Binary Tree to destroy.
 */
void btDestroyAll(BinaryTree_t *tree);

/**
 * Prints the Binary Tree.
 * @param tree The Binary Tree to print.
 */
void printTree(BinaryTree_t *tree,
               void (*repr)(BTNode_t *node, char *buffer, int bufferSize),
               int nodeReprBuffer);

#endif
