#include "tree.h"
#include <stdlib.h>

typedef struct Value {
	int number;
	char symbol;
} Value;

typedef struct Node {
	Value value;
	Node* right;
	Node* left;
} Node;

typedef struct Tree {
	Node* root;
} Tree;

Tree* createTree(void) {
	Tree* tree = calloc(1, sizeof(tree));
	return tree;
}

Node* createNode(Tree* tree) {
	Node* temp = calloc(1, sizeof(Node));
	return temp;
}