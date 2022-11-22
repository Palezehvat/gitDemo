#include "avlTree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Value {
	int key;
	char* value;
	int balance;
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

void helpedClearTree(Node* root) {
	if (root != NULL) {
		helpedClearTree(root->left);
		helpedClearTree(root->right);
		free(root->data.value);
		free(root);
		root = NULL;
	}
}

void clearTree(Tree* tree) {
	if (tree == NULL) {
		return;
	}
	helpedClearTree(tree->root);
	free(tree);
	tree = NULL;
}

Node* rotateLeft(Node* a)
{
	Node* b = a->right;
	Node* c = b->left;
	b->left = a;
	a->right = c;
	return b;
}

Node* bigRotateLeft(Node* a) {
	Node* b = a->right;
	Node* c = b->left;
	a->right = c->left;
	b->left = c->right;
	c->left = a;
	c->right = b;
	return c;
}

Node* bigRotateRight(Node* a) {
	Node* b = a->left;
	Node* c = b->right;
	a->left = c->right;
	b->right = c->left;
	c->left = b;
	c->right = a;
	return c;
}

Node* rotateLeft(Node* a) {
	Node* b = a->right;
	Node* c = b->left;
	b->left = a;
	a->right = c;
	return b;
}

Node* rotateRight(Node* a) {
	Node* b = a->left;
	Node* c = b->right;
	b->right = a;
	a->left = c;
	return b;
}

Node* balance(Node* node) {
	if (node->data.balance == 2) {
		if (node->right->data.balance >= 0)
			return rotateLeft(node);
		return bigRotateLeft(node);
	}
	if (node->data.balance == -2) {
		if (node->left->data.balance <= 0)
			return rotateRight(node);
		return bigRotateRight(node);
	}
	return node;
}

Node* helpedToInsert(Node* root, int key, char* string) {
	if (root == NULL) {
		Node* newNode = createElementTree();
		newNode->data.value = string;
		newNode->data.key = key;
		return newNode;
	}
	if (root->data.key == key) {
		root->data.value = string;
		return root;
	}
	if (key < root->data.key) {
		root->left = helpedToInsert(root->left, key, string);
		--root->data.balance;
	}
	else {
		root->right = helpedToInsert(root->right, key, string);
		++root->data.balance;
	}
	return balance(root);
}

void addToTree(Tree* tree, int key, char* string) {
	tree->root = helpedToInsert(tree->root, key, string);
}

char* returnValueByKey(Tree* tree, int key) {
	if (tree == NULL) {
		return NULL;
	}
	Node* walker = tree->root;

	while (walker != NULL) {
		if (walker->data.key == key) {
			return walker->data.value;
		}
		if (walker->data.key < key) {
			walker = walker->right;
		}
		else {
			walker = walker->left;
		}
	}
	return NULL;
}

bool isKeyInTree(Tree* tree, int key) {
	if (tree == NULL) {
		return false;
	}
	Node* walker = tree->root;

	while (walker != NULL) {
		if (walker->data.key == key) {
			return true;
		}
		if (walker->data.key < key) {
			walker = walker->right;
		}
		else {
			walker = walker->left;
		}
	}
	return false;
}

Node* deleteNode(Node* root, int key, Tree* tree, Node* previousRoot) {

}

Node* helpDeleteNodeInTreeByKey(Node* root, int key, Tree* tree, Node* previousRoot) {
	if (root == NULL) {
		return NULL;
	}
	if (root->data.key == key) {
		if (previousRoot == NULL) {
			if (root->right == NULL) {
				Node* temp = root->left;
				free(root->data.value);
				free(root);
				return temp;
			}
			else {
				if (root->right->left == NULL) {
					Node* temp = root->left;
					free(root->data.value);
					free(root);
					root->left = temp;
					root->data.balance = root->right - root->left;
					return root;
				}
				else {
					deleteNode(root, key, tree, previousRoot);
				}
			}
		}
		else {
			if (previousRoot->data.key < key) {
				previousRoot->right = deleteNode(root, key, tree, previousRoot);
			}
			else {
				previousRoot->left = deleteNode(root, key, tree, previousRoot);
			}
		}
	}
	if (key < root->data.key) {
		root->left = helpDeleteNodeInTreeByKey(root->left, key, tree, root);
		++root->data.balance;
	}
	else {
		root->right = helpDeleteNodeInTreeByKey(root->right, key, tree, root);
		--root->data.balance;
	}
	return balance(root);
}

void deleteNodeInTreeByKey(Tree* tree, int key) {
	tree->root = helpedDeleteNodeInTreeByKey(tree->root, key, tree, NULL);
}