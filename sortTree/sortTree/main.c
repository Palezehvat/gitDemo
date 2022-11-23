#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int scanOneInt();

bool test() {
	int arrayOut[3] = { 2, 1, 3 };
	int correctArray[3] = { 1, 2, 3 };
	addArrayToTree(arrayOut, 3);
	for (int i = 0; i < 3; ++i) {
		if (arrayOut[i] != correctArray[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	if (test()) {
		printf("Test correct\n");
	} else {
		printf("Error\n");
		return -1;
	}
	printf("Input size and elements\n");
	int size = scanOneInt();
	int* arrayOut = calloc(size, sizeof(int));
	if (arrayOut == NULL) {
		printf("%s", "Error \n");
		return -1;
	}
	for (int i = 0; i < size; ++i) {
		arrayOut[i] = scanOneInt();
	}

	addArrayToTree(arrayOut, size);

	for (int i = 0; i < size; ++i) {
		printf("%d ", arrayOut[i]);
	}
}

int scanOneInt() {
	int number = 0;
	int checkScanf = scanf("%d", &number);

	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}

		printf("%s", "Error \n");
		checkScanf = scanf("%d", &number);
	}

	return number;
}