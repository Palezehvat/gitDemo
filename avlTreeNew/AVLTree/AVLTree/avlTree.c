#include "avlTree.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Value {
	char key[100];
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
		b->data.balance += 1;
		a->data.balance += -1;
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
		b->data.balance += -1;
		a->data.balance += 1;
	} else {
		a->data.balance = 0;
		b->data.balance = 0;
	}
	b->right = a;
	a->left = c;
	return b;
}

Node* balance(Node* node) {
	if (node->data.balance == 2) {
		if (node->right->data.balance >= 0)
			return rotateLeft(node);
		node->right =  rotateRight(node->right);
		return rotateLeft(node);
	}
	if (node->data.balance == -2) {
		if (node->left->data.balance <= 0)
			return rotateRight(node);
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	return node;
}

Node* helpedToInsert(Node* root, const char* key, char* string, const bool isKeyInTree, bool* needToChangeBalance) {
	if (root == NULL) {
		Node* newNode = createElementTree();
		newNode->data.value = string;
		strcpy(newNode->data.key, key);
		return newNode;
	}
	if (strcmp(root->data.key, key) == 0) {
		root->data.value = string;
		return root;
	}
	if (strcmp(key, root->data.key) == -1) {
		root->left = helpedToInsert(root->left, key, string, isKeyInTree, needToChangeBalance);
		if (!isKeyInTree && !*needToChangeBalance) {
			--root->data.balance;
		}
	}
	else {
		root->right = helpedToInsert(root->right, key, string, isKeyInTree, needToChangeBalance);
		if (!isKeyInTree && !*needToChangeBalance) {
			++root->data.balance;
		}
	}
	if (root->data.balance == 0) {
		*needToChangeBalance = true;
	}
	Node* temp = balance(root);
	if (temp->data.balance == 0) {
		*needToChangeBalance = true;
	}
	return temp;
}

void addToTree(Tree* tree, const char* key, char* string) {
	bool needToChangeBalance = false;
	tree->root = helpedToInsert(tree->root, key, string, isKeyInTree(tree, key), &needToChangeBalance);
}

char* returnValueByKey(Tree* tree, const char* key) {
	if (tree == NULL) {
		return NULL;
	}
	Node* walker = tree->root;

	while (walker != NULL) {
		if (strcmp(walker->data.key, key) == 0) {
			return walker->data.value;
		}
		if (strcmp(walker->data.key, key) == -1) {
			walker = walker->right;
		}
		else {
			walker = walker->left;
		}
	}
	return NULL;
}

bool isKeyInTree(Tree* tree, const char* key) {
	if (tree == NULL) {
		return false;
	}
	Node* walker = tree->root;

	while (walker != NULL) {
		if (strcmp(walker->data.key, key) == 0) {
			return true;
		}
		if (strcmp(walker->data.key, key) == -1) {
			walker = walker->right;
		}
		else {
			walker = walker->left;
		}
	}
	return false;
}

Node* deleteNode(Node* root, const char* key, Tree* tree, Node* previousRoot, Node* theMostBigLeft, bool firstLeft, bool* needToChangeBalance, Node* previousMostBigLeft) {
	if (!firstLeft && theMostBigLeft->right == NULL) {
		Node* tempLeft = root->left;
		free(root->data.value);
		root->data.value = theMostBigLeft->data.value;
		strcpy(root->data.key, theMostBigLeft->data.key);
		if (theMostBigLeft->left != NULL && previousMostBigLeft != root) {
			previousMostBigLeft->right = theMostBigLeft->left;
		}
		free(theMostBigLeft);
		return NULL;
	} else {
		if (firstLeft) {
			root->left = deleteNode(root, key, tree, previousRoot, root->left, false, needToChangeBalance, root);
			if (!*needToChangeBalance) {
				++root->data.balance;
			}
			if (root->data.balance == -1 || root->data.balance == 1) {
				*needToChangeBalance = true;
			}
			Node* temp = balance(root);
			if (temp->data.balance == -1 || temp->data.balance == 1) {
				*needToChangeBalance = true;
			}
			return temp;
		}
		else {
			theMostBigLeft->right = deleteNode(root, key, tree, previousRoot, theMostBigLeft->right, false, needToChangeBalance, theMostBigLeft);
			if (!*needToChangeBalance) {
				--theMostBigLeft->data.balance;
			}
			if (theMostBigLeft->right == NULL) {
				return theMostBigLeft;
			}
		}
	}
	if (root->data.balance == -1 || root->data.balance == 1) {
		*needToChangeBalance = true;
	}
	Node* temp = balance(theMostBigLeft);
	if (temp->data.balance == -1 || temp->data.balance == 1) {
		*needToChangeBalance = true;
	}
	return temp;
}

Node* helpDeleteNodeInTreeByKey(Node* root, const char* key, Tree* tree, Node* previousRoot, bool* needToChangeBalance) {
	if (root == NULL) {
		return NULL;
	}
	if (strcmp(root->data.key, key) == 0) {
		if (root->left == NULL) {
			Node* temp = root->right;
			free(root->data.value);
			free(root);
			if (previousRoot == NULL) {
				tree->root = temp;
			}
			else {
				if (strcmp(previousRoot->data.key, key) == -1) {
					previousRoot->right = temp;
				}
				else {
					previousRoot->left = temp;
				}
			}
			return temp;
		}
		root = deleteNode(root, key, tree, previousRoot, NULL, true, needToChangeBalance, root);
		if (previousRoot == NULL) {
			tree->root = root;
		}
		else {
			if (strcmp(previousRoot->data.key, key) == -1) {
				previousRoot->right = root;
			}
			else {
				previousRoot->left = root;
			}
		}
		return root;
	}
	if (strcmp(key, root->data.key) == -1) {
		root->left = helpDeleteNodeInTreeByKey(root->left, key, tree, root, needToChangeBalance);
		if (!*needToChangeBalance) {
			++root->data.balance;
		}
	}
	else {
		root->right = helpDeleteNodeInTreeByKey(root->right, key, tree, root, needToChangeBalance);
		if (!*needToChangeBalance) {
			--root->data.balance;
		}
	}
	if (root->data.balance == -1 || root->data.balance == 1) {
		*needToChangeBalance = true;
	}
	Node* temp = balance(root);
	if (temp->data.balance == -1 || temp->data.balance == 1) {
		*needToChangeBalance = true;
	}
	return temp;
}

void deleteNodeInTreeByKey(Tree* tree, const char* key) {
	if (isKeyInTree(tree, key)) {
		bool needToChangeBalance = false;
		tree->root = helpDeleteNodeInTreeByKey(tree->root, key, tree, NULL, &needToChangeBalance);
	}
}