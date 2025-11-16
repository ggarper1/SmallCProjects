# 📚 Utils Library Documentation

This document provides comprehensive documentation for the custom data structures library included in this repository. All data structures are implemented in C using basic libraries.

---

## 📋 Notes

### Memory Management
- **Data Storage**: All data structures store pointers to values, not the values themselves
- **User Responsibility**: The caller is responsible for:
  - Memory allocation before storing values in the data structures
  - Handling type casting when retrieving values
  - Freeing removed elements from the data structure
- **Destruction Methods**:
  These data structures have two destruction methods:
  - `destroy()`: Frees only the data structure itself.
  - `destroyAll()`: Frees the data structure AND all elements stored within it
  
  If you use `destroy()` instead of `destroyAll()`, ensure you free all stored values to avoid memory leaks.

### Type Safety
Since these structures use `void*` pointers, type safety is the user's responsibility. Always ensure proper casting when inserting and retrieving values.

---

## 📂 File Structure

```
utils/
├── include/
│   ├── binaryTree.h
│   ├── queue.h
│   ├── stack.h
│   ├── print.h
│   ├── random.h
│   └── sort.h
├── src/
│   ├── binaryTree.c
│   ├── queue.c
│   ├── stack.c
│   ├── print.c
│   ├── random.c
│   └── sort.c
└── tests/
    ├── binaryTreeTests.c
    ├── queueTests.c
    └── stackTests.c
```
---

## 📦 Data Structures

### Stack (`stack.h`)

A Last-In-First-Out (LIFO) data structure with dynamic capacity.

#### Type Definition
```c
typedef struct Stack Stack_t;
```

#### Functions

**`Stack_t *newStack(size_t capacity)`**
- Creates a new stack with an initial capacity
- **Parameters**: `capacity` - Initial number of items the stack can hold
- **Returns**: Pointer to the new Stack, or NULL on failure

**`int sLength(Stack_t *stack)`**
- Returns the number of elements currently in the stack
- **Parameters**: `stack` - The Stack
- **Returns**: Number of items in the stack

**`void *sPeek(Stack_t *stack)`**
- Retrieves the top element without removing it
- **Parameters**: `stack` - The Stack
- **Returns**: Pointer to the top element, or NULL if empty

**`void sPush(Stack_t *stack, void *value)`**
- Adds a value to the top of the stack
- **Parameters**: 
  - `stack` - The Stack
  - `value` - Pointer to the value to add
- **Note**: Caller manages memory for the value

**`void *sPop(Stack_t *stack)`**
- Removes and returns the top element
- **Parameters**: `stack` - The Stack
- **Returns**: Pointer to the removed value, or NULL if empty
- **Note**: Caller is responsible for freeing the returned value

**`void sDestroy(Stack_t *stack)`**
- Frees the stack structure only
- **Parameters**: `stack` - The Stack to destroy
- **Note**: Does not free stored values

**`void sDestroyAll(Stack_t *stack)`**
- Frees the stack structure and all stored values
- **Parameters**: `stack` - The Stack to destroy
- **Warning**: After calling this, accessing previously stored elements causes undefined behavior

**`void printStack(Stack_t *stack, void (*repr)(void *value, char *buffer, int bufferSize), int bufferSize)`**
- Prints the stack contents
- **Parameters**:
  - `stack` - The Stack to print
  - `repr` - Function to convert values to string representation
  - `bufferSize` - Size of the string buffer

---

### Queue (`queue.h`)

A First-In-First-Out (FIFO) data structure with dynamic capacity.

#### Type Definition
```c
typedef struct Queue Queue_t;
```

#### Functions

**`Queue_t *newQueue(size_t capacity)`**
- Creates a new queue with an initial capacity
- **Parameters**: `capacity` - Initial number of items the queue can hold
- **Returns**: Pointer to the new Queue, or NULL on failure

**`int qLength(Queue_t *queue)`**
- Returns the number of elements currently in the queue
- **Parameters**: `queue` - The Queue
- **Returns**: Number of items in the queue

**`void *qPeek(Queue_t *queue)`**
- Retrieves the front element without removing it
- **Parameters**: `queue` - The Queue
- **Returns**: Pointer to the front element, or NULL if empty

**`void qAdd(Queue_t *queue, void *value)`**
- Adds a value to the back of the queue
- **Parameters**: 
  - `queue` - The Queue
  - `value` - Pointer to the value to add
- **Note**: Caller manages memory for the value

**`void *qRemove(Queue_t *queue)`**
- Removes and returns the front element
- **Parameters**: `queue` - The Queue
- **Returns**: Pointer to the removed value, or NULL if empty
- **Note**: Caller is responsible for freeing the returned value

**`void qDestroy(Queue_t *queue)`**
- Frees the queue structure only
- **Parameters**: `queue` - The Queue to destroy
- **Note**: Does not free stored values

**`void qDestroyAll(Queue_t *queue)`**
- Frees the queue structure and all stored values
- **Parameters**: `queue` - The Queue to destroy
- **Warning**: After calling this, accessing previously stored elements causes undefined behavior

**`void printQueue(Queue_t *queue, void (*repr)(void *value, char *buffer, int bufferSize), int bufferSize)`**
- Prints the queue contents
- **Parameters**:
  - `queue` - The Queue to print
  - `repr` - Function to convert values to string representation
  - `bufferSize` - Size of the string buffer

---

### Binary Tree (`binaryTree.h`)

A binary search tree implementation that maintains sorted order based on a user-provided comparison function.

#### Type Definitions
```c
typedef struct BTNode {
  void *value;
  struct BTNode *right;
  struct BTNode *left;
} BTNode_t;

typedef struct BinaryTree {
  size_t length;
  int height;
  BTNode_t *root;
  int (*compare_func)(const void *item1, const void *item2);
} BinaryTree_t;
```

#### Functions

**`BinaryTree_t *newBinaryTree(int (*compare_func)(const void *item1, const void *item2))`**
- Creates a new Binary Search Tree
- **Parameters**: `compare_func` - Function to compare items (should return negative if item1 < item2, 0 if equal, positive if item1 > item2)
- **Returns**: Pointer to the new BinaryTree, or NULL on failure

**`BTNode_t *btFind(BinaryTree_t *tree, void *item)`**
- Searches for an element in the tree
- **Parameters**: 
  - `tree` - The Binary Tree
  - `item` - Pointer to the item to find
- **Returns**: Pointer to the node containing the element, or NULL if not found

**`BTNode_t *btInsert(BinaryTree_t *tree, void *item)`**
- Inserts an item into the tree
- **Parameters**: 
  - `tree` - The Binary Tree
  - `item` - Pointer to the item to insert
- **Returns**: Pointer to the new node, or NULL on failure
- **Note**: Caller manages memory for the item

**`void *btRemove(BinaryTree_t *tree, const void *value)`**
- Removes an item from the tree
- **Parameters**: 
  - `tree` - The Binary Tree
  - `value` - Pointer to the value to remove
- **Returns**: Pointer to the removed value, or NULL if not found
- **Note**: Caller is responsible for freeing the returned value

**`void btDestroy(BinaryTree_t *tree)`**
- Frees the tree structure only
- **Parameters**: `tree` - The BinaryTree to destroy
- **Note**: Does not free stored values

**`void btDestroyAll(BinaryTree_t *tree)`**
- Frees the tree structure and all stored values
- **Parameters**: `tree` - The Binary Tree to destroy
- **Warning**: After calling this, accessing previously stored elements causes undefined behavior

**`void printTree(BinaryTree_t *tree, void (*repr)(BTNode_t *value, char *buffer, int bufferSize), int bufferSize)`**
- Prints the tree structure
- **Parameters**:
  - `tree` - The Binary Tree to print
  - `repr` - Function to convert node values to string representation
  - `bufferSize` - Size of the string buffer

---

## 💡 Usage Examples

### Stack Example
```c
#include "utils/include/stack.h"
#include <stdlib.h>

// Create a stack for integers
Stack_t *stack = newStack(10);

// Push values
int *val = malloc(sizeof(int));
*val = 42;
sPush(stack, val);

// Pop value
int *retrieved = (int *)sPop(stack);
printf("Value: %d\n", *retrieved);
free(retrieved);

// Clean up
sDestroy(stack);
```

### Queue Example
```c
#include "utils/include/queue.h"
#include <stdlib.h>

// Create a queue
Queue_t *queue = newQueue(10);

// Add values
int *val = malloc(sizeof(int));
*val = 100;
qAdd(queue, val);

// Remove value
int *retrieved = (int *)qRemove(queue);
free(retrieved);

// Clean up
qDestroy(queue);
```

### Binary Tree Example
```c
#include "utils/include/binaryTree.h"
#include <stdlib.h>

// Comparison function for integers
int compareInts(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Create tree
BinaryTree_t *tree = newBinaryTree(compareInts);

// Insert values
int *val = malloc(sizeof(int));
*val = 50;
btInsert(tree, val);

// Find value
BTNode_t *node = btFind(tree, val);
if (node) {
    printf("Found: %d\n", *(int *)node->value);
}

// Remove and clean up
void *removed = btRemove(tree, val);
free(removed);
btDestroy(tree);
```

