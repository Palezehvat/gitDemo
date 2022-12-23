#include "avlTree.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool testForAvlTree() {
	Tree* tree = createTree();
	char* string1 = calloc(2, sizeof(char));
	if (string1 == NULL) {
		return false;
	}
	string1[0] = 'a';
	char key1[] = "320";
	addToTree(tree, key1, string1);
	char* string2 = calloc(2, sizeof(char));
	if (string2 == NULL) {
		free(string1);
		return false;
	}
	string2[0] = 'b';
	char key2[] = "200";
	addToTree(tree, key2, string2);
	char* string3 = calloc(2, sizeof(char));
	if (string3 == NULL) {
		clearTree(tree);
		return false;
	}
	string3[0] = 'c';
	char key3[] = "100";
	addToTree(tree, key3, string3);
	if (!isKeyInTree(tree, "100")) {
		clearTree(tree);
		return false;
	}
	for (int i = 0; i < 1000; ++i) {
		char buffer[5] = { '\0' };
		_itoa(i, buffer, 10);
		addToTree(tree, buffer, calloc(1, sizeof(char)));
	}
	if (!checkBalance(tree)) {
		clearTree(tree);
		return false;
	}
	deleteNodeInTreeByKey(tree, "100", true);
	if (isKeyInTree(tree, "100")) {
		clearTree(tree);
		return false;
	}
	deleteNodeInTreeByKey(tree, "200", true);
	char stringForCheck[2] = { '\0' };
	stringForCheck[0] = 'a';
	if (strcmp(returnValueByKey(tree, "320"), stringForCheck) != 0) {
		clearTree(tree);
		return false;
	}
	deleteNodeInTreeByKey(tree, "320", true);
	clearTree(tree);
	return true;
}