#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct BinaryTree BinaryTree;

typedef enum Error {
	memoryError,
	emptyPointer,
	anotherError,
	ok,
}Error;

BinaryTree* createBinaryTree(Error* errorCheck);

char* addToBinaryTree(BinaryTree* tree, Error* errorCheck, int key, char* value);

char* deleteNodeInBinaryTree(BinaryTree* tree, Error* errorCheck, int key);

bool isEmptyTree(BinaryTree* tree);

BinaryTree* clearTree(BinaryTree* tree);