#ifndef BINARY_TREE_H 
#define BINARY_TREE_H

#include <stdbool.h>

typedef struct Node Node;

Node* addToBinaryTree(Node* tree, const int key, const char* value);

char* returnValueByKey(Node* tree, const int key);

void clearBinaryTree(Node* tree);

Node* deleteNodeInTreeByKey(Node* tree, const int key);

Node* createNode(const int key, const char* value);

bool isKeyInTree(Node* tree, const int key);

#endif