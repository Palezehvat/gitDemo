#include "avlTree.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool testForAvlTree() {
	FILE* file = fopen("test.txt", "r");
	if (file == NULL) {
		return false;
	}
	Tree* tree = createTree();
	int key = 0;
	char string[2] = { '\0' };
	string[0] = 'a';
	while (fscanf(file, "%d", &key) == 1) {
		addToTree(tree, key, string);
	}
	fclose(file);

	if (!isKeyInTree(tree, 100)) {
		return false;
	}
	deleteNodeInTreeByKey(tree, 100, true);
	if (isKeyInTree(tree, 100)) {
		return false;
	}
	deleteNodeInTreeByKey(tree, 80, true);
	char stringForCheck[2] = { '\0' };
	stringForCheck[0] = 'a';
	if (strcmp(returnValueByKey(tree, 120), stringForCheck) != 0) {
		return false;
	}
	deleteNodeInTreeByKey(tree, 120, true);
	clearTree(tree);
	return true;
}