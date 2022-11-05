#include "avlTree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Value {
	int key;
	char value;
} Value;

typedef struct Node {
	Value data;
	Node* left;
	Node* right;
} Node;

typedef struct Tree {
	Node* root
} Tree;

Tree* createTree(void) {
	Tree* tree = calloc(1, sizeof(Tree));
	return tree;
}

Node* createElementTree(void) {
	Node* temp = calloc(1, sizeof(Node));
	return temp;
}