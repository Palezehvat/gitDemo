#include "avlTree.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Value {
	int key;
	char* value;
	int balance;
} Value;

typedef struct Node {
	Value data;
	struct Node* left;
	struct Node* right;
} Node;

typedef struct Tree {
	struct Node* root;
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
	if (b->data.balance == 0) {
		b->data.balance = 1;
		a->data.balance = -1;
	} else {
		b->data.balance = 0;
		a->data.balance = 0;
	}
	b->left = a;
	a->right = c;
	return b;
}
 
Node* rotateRight(Node* a) {
	Node* b = a->left;
	Node* c = b->right;
	if (b->data.balance == 0) {
		b->data.balance = -1;
		a->data.balance = 1;
	} else {
		a->data.balance = 0;
		b->data.balance = 0;
	}
	b->right = a;
	a->left = c;
	return b;
}

Node* balance(Node* node, bool* wasBalance) {
	if (node->data.balance == 2) {
		if (node->right->data.balance < 0)
			node->right = rotateLeft(node->right);
		*wasBalance = true;
		return rotateLeft(node);
	}
	if (node->data.balance == -2) {
		if (node->left->data.balance > 0)
			node->left = rotateRight(node->left);
		*wasBalance = true;
		return rotateRight(node);
	}
	return node;
}

Node* helpedToInsert(Node* root, int key, char* string, const bool isKeyInTree, bool* wasBalance) {
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
		root->left = helpedToInsert(root->left, key, string, isKeyInTree, wasBalance);
		if (!isKeyInTree && !*wasBalance) {
			--root->data.balance;
		}
	}
	else {
		root->right = helpedToInsert(root->right, key, string, isKeyInTree, wasBalance);
		if (!isKeyInTree && !*wasBalance) {
			++root->data.balance;
		}
	}
	return balance(root, wasBalance);
}

void addToTree(Tree* tree, int key, char* string) {
	bool wasBalance = false;
	tree->root = helpedToInsert(tree->root, key, string, isKeyInTree(tree, key), &wasBalance);
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

Node* deleteNode(Node* root, int key, Tree* tree, Node* previousRoot, Node* theMostBigLeft, bool firstLeft, const bool ifUseFile, bool* wasBalance) {
	if (!firstLeft && theMostBigLeft->right == NULL) {
		Node* tempLeft = root->left;
		if (!ifUseFile) {
			free(root->data.value);
			root->data.value = theMostBigLeft->data.value;
		}
		root->data.key = theMostBigLeft->data.key;
		if (theMostBigLeft->left != NULL) {
			root->left = theMostBigLeft->left;
			root->left->left = tempLeft;
			root->left->data.balance = -1 + root->left->left->data.balance;
		}
		root->data.balance = root->right->data.balance - root->left->data.balance + 1;
		free(theMostBigLeft);
		return NULL;
	} else {
		if (firstLeft) {
			root->left = deleteNode(root, key, tree, previousRoot, root->left, false, ifUseFile, wasBalance);
			if (root->left == NULL) {
				return balance(root, wasBalance);
			}
			return balance(root, wasBalance);
		}
		else {
			theMostBigLeft->right = deleteNode(root, key, tree, previousRoot, theMostBigLeft->right, false, ifUseFile, wasBalance);
			--theMostBigLeft->data.balance;
			if (theMostBigLeft->right == NULL) {
				return theMostBigLeft;
			}
		}
	}
	return balance(theMostBigLeft, wasBalance);
}

Node* helpDeleteNodeInTreeByKey(Node* root, int key, Tree* tree, Node* previousRoot, const bool ifUseFile, bool* wasBalance) {
	if (root == NULL) {
		return NULL;
	}
	if (root->data.key == key) {
		if (root->left == NULL) {
			Node* temp = root->right;
			if (!ifUseFile) {
				free(root->data.value);
			}
			free(root);
			if (previousRoot == NULL) {
				tree->root = temp;
			} else {
				if (previousRoot->data.key < key) {
					previousRoot->right = temp;
				} else {
					previousRoot->left = temp;
				}
			}
			return temp;
		}
		root = deleteNode(root, key, tree, previousRoot, NULL, true, ifUseFile, wasBalance);
		if (previousRoot == NULL) {
			tree->root = root;
		} else {
			if (previousRoot->data.key < key) {
				previousRoot->right = root;
			}
			else {
				previousRoot->left = root;
			}
		}
		return root;
	}
	if (key < root->data.key) {
		root->left = helpDeleteNodeInTreeByKey(root->left, key, tree, root, ifUseFile, wasBalance);
		++root->data.balance;
	}
	else {
		root->right = helpDeleteNodeInTreeByKey(root->right, key, tree, root, ifUseFile, wasBalance);
		--root->data.balance;
	}
	return balance(root, wasBalance);
}

void deleteNodeInTreeByKey(Tree* tree, int key, const bool ifUseFile) {
	if (isKeyInTree(tree, key)) {
		bool wasBalance = false;
		tree->root = helpDeleteNodeInTreeByKey(tree->root, key, tree, NULL, ifUseFile, &wasBalance);
	}
}