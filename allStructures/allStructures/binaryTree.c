#include "binaryTree.h"

typedef struct Node{
	struct Node* left;
	struct Node* right;
	int key;
	char* value;
}Node;

typedef struct BinaryTree {
	struct Node* root;
}BinaryTree;

BinaryTree* createBinaryTree(Error* errorCheck) {
	BinaryTree* tree = calloc(1, sizeof(BinaryTree));
	if (tree == NULL) {
		*errorCheck = memoryError;
	}
	return tree;
}

char* addToBinaryTree(BinaryTree* tree, Error* errorCheck, int key, char* value) {
	if (tree == NULL) {
		*errorCheck = emptyPointer;
		return NULL;
	}
	Node* temp = calloc(1, sizeof(Node));
	if (temp == NULL) {
		*errorCheck = memoryError;
		return NULL;
	}
	temp->value = value;
	temp->key = key;
	if (tree->root == NULL) {
		tree->root = temp;
		return NULL;
	}
	Node* walker = tree->root;
	while (walker != NULL) {
		if (walker->key < key) {
			if (walker->right == NULL) {
				walker->right = temp;
				return NULL;
			}
			walker = walker->right;
		} else if (walker->key > key) {
			if (walker->left == NULL) {
				walker->left = temp;
				return NULL;
			}
			walker = walker->left;
		} else {
			char* valueFromWalker = walker->value;
			walker->value = value;
			return valueFromWalker;
		}
	}
	return NULL;
}

char* deleteNodeInBinaryTree(BinaryTree* tree, Error* errorCheck, int key) {
	if (tree == NULL || tree->root == NULL) {
		*errorCheck = emptyPointer;
		return NULL;
	}
	Node* walker = tree->root;
	Node* prevWalker = walker;
	while (walker != NULL) {
		if (walker->key == key) {
			Node* walkerLeft = walker->left;
			Node* walkerRight = walker->right;
			char* value = walker->value;
			if (walker->left == NULL) {
				if (walker == prevWalker) {
					tree->root = walkerRight;
				} else if (key > prevWalker->key) {
					prevWalker->right = walkerRight;
				} else {
					prevWalker->left = walkerRight;
				}
				free(walker);
				return value;
			} else {
				Node* newWalker = walkerLeft->right;
				if (newWalker == NULL) {
					if (walker == prevWalker) {
						tree->root = walkerLeft;
					} else if (key > prevWalker->key) {
						prevWalker->right = walkerLeft;
					} else {
						prevWalker->left = walkerLeft;
					}
					walkerLeft->right = walkerRight;
					free(walker);
					return value;
				} else {
					Node* prevNewWalker = newWalker;
					while (newWalker->right != NULL) {
						prevNewWalker = newWalker;
						newWalker = newWalker->right;
					}
					newWalker->left = walkerLeft;
					newWalker->right = walkerRight;
					if (prevNewWalker == newWalker) {
						walkerLeft->right = NULL;
					} else {
						prevNewWalker->right = NULL;
					}
					if (walker == prevWalker) {
						tree->root = newWalker;
					} else if (key > prevWalker->key) {
						prevWalker->right = newWalker;
					} else {
						prevWalker->left = newWalker;
					}
					free(walker);
					return value;

				}
			}
		} else if (walker->key < key) {
			prevWalker = walker;
			walker = walker->right;
		} else {
			prevWalker = walker;
			walker = walker->left;
		}
	}
	return NULL;
}

bool isEmptyTree(BinaryTree* tree) {
	if (tree == NULL) {
		return true;
	}
	return tree->root == NULL;
}

void helpedToDelete(Node* root) {
	if (root) {
		helpedToDelete(root->left);
		helpedToDelete(root->right);
		free(root);
	}
}

BinaryTree* clearTree(BinaryTree* tree) {
	if (tree == NULL) {
		return NULL;
	}
	helpedToDelete(tree->root);
	free(tree);
	return NULL;
}
