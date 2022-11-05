#include "tree.h"
#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>

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

Node* createNode(void) {
	Node* temp = calloc(1, sizeof(Node));
	return temp;
}

Node* nonRecursivePreorder(Node* root, int* errorCode) {
	Stack* stack = createStack();
	Node* current = root;
	while (true) {
		if (current != NULL) {
			if (current->value.symbol == 0 && current->value.number == 0) {
				return current;
			}
			push(stack, current);
			current = current->left;
		}
		else {
			if (isEmpty(stack)) {
				free(stack);
				return NULL;
			}
			current = pop(stack, errorCode);
			if (*errorCode != 0) {
				return NULL;
			}
			current = current->right;
		}
	}
	deleteStack(stack);
	return NULL;
}

void addToTreeSymbol(Tree* tree, char symbol, int* errorCode) {
	if (tree == NULL) {
		*errorCode = -1;
		return;
	}
	if (tree->root == NULL) {
		tree->root = createNode();
		if (tree->root == NULL) {
			*errorCode = -1;
			return;
		}
		tree->root->value.symbol = symbol;
		tree->root->left = createNode();
		if (tree->root->left == NULL) {
			*errorCode = -1;
			return;
		}
		tree->root->right = createNode();
		if (tree->root == NULL) {
			*errorCode = -1;
			return;
		}
		return;
	}
	Node* newRoot = nonRecursivePreorder(tree->root, errorCode);
	if (*errorCode != 0 || newRoot == NULL) {
		*errorCode = -1;
		return;
	}
	newRoot->value.symbol = symbol;
	newRoot->left = createNode();
	if (newRoot->left == NULL) {
		*errorCode = -1;
		return;
	}
	newRoot->right = createNode();
	if (newRoot->right == NULL) {
		*errorCode = -1;
		return;
	}
}

void addToTreeNumber(Tree* tree, int number, int* errorCode) {
	
	if (tree == NULL || tree->root == NULL) {
		*errorCode = -1;
		return;
	}
	Node* newRoot = nonRecursivePreorder(tree->root, errorCode);
	if (*errorCode != 0 || newRoot == NULL) {
		*errorCode = -1;
		return;
	}
	newRoot->value.number = number;
}

void postorderHelp(Node* root, Stack* stack) {
	if (root != NULL) {
		postorderHelp(root->left, stack);
		postorderHelp(root->right, stack);
		if (root->value.symbol != 0) {
			int errorCode = 0;
			Node* element = pop(stack, &errorCode);
			int secondNumber = element->value.number;
			element = pop(stack, &errorCode);
			Node* newElement = createNode();
			int firstNumber = element->value.number;
			int newNumber = 0;
			if (root->value.symbol == '+') {
				newNumber = secondNumber + firstNumber;
			} else if (root->value.symbol == '*') {
				newNumber = secondNumber * firstNumber;
			} else if (root->value.symbol == '-') {
				newNumber = secondNumber - firstNumber;
			} else {
				newNumber = secondNumber / firstNumber;
			}
			newElement->value.number = newNumber;
			push(stack, newElement);
		} else {
			push(stack, root);
		}///�������� ������ ������, ��������� ��������
	}
}

int postorderCount(Tree* tree, int* errorCode) {
	Stack* stack = createStack();
	postorderHelp(tree->root, stack);
	Node* newElement = pop(stack, errorCode);
	if (*errorCode != 0 || newElement == NULL) {
		return 0;
	}
	return newElement->value.number;
}