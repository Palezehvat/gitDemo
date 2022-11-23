#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
	int value;
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

Node* createNode(void) {
	Node* temp = calloc(1, sizeof(Node));
	return temp;
}

void addToTree(Tree* tree, int value) {
	if (tree == NULL) {
		return ;
	}
	if (tree->root == NULL) {
		tree->root = createNode();
		tree->root->value = value;
		return;
	} 
	Node* walker = tree->root;
	while (walker) {
		if (walker->value > value) {
			if (walker->left == NULL) {
				Node* temp = createNode();
				temp->value = value;
				walker->left = temp;
				return;
			}
			walker = walker->left;
		} else {
			if (walker->right == NULL) {
				Node* temp = createNode();
				temp->value = value;
				walker->right = temp;
				return;
			}
			walker = walker->right;
		}
	}
}

int j = 0;

void helpedInOrder(Node* root, int arrayOut[]) {
	if (root != NULL) {
		helpedInOrder(root->left, arrayOut);
		arrayOut[j] = root->value;
		++j;
		helpedInOrder(root->right, arrayOut);
	}
}

void inOrder(Tree* tree, int arrayOut[]) {
	helpedInOrder(tree->root, arrayOut);
	j = 0;
}

void helpBackOrderClear(Node* root) {
	if (root != NULL) {
		helpBackOrderClear(root->left);
		helpBackOrderClear(root->right);
		free(root);
	}
}

void backOrderClear(Tree* tree) {
	helpBackOrderClear(tree->root);
}

void addArrayToTree(int arrayOut[], int size) {
	Tree* tree = createTree();

	for (int i = 0; i < size; ++i) {
		addToTree(tree, arrayOut[i]);
	}

	inOrder(tree, arrayOut);
	backOrderClear(tree);
}