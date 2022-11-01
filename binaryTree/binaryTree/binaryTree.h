#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node Node;

Node* addToBinaryTree(Node* tree, int key, char* value);

char* returnValueByKey(Node* tree, int key);

void clearBinaryTree(Node* tree);

bool deleteNodeInTreeByKey(Node* tree, int key);

bool isThereAKeyInTheTree(Node* tree, int key);