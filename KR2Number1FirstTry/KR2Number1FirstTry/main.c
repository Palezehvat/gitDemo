#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

int workWithFile(char fileName[]) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("File not found!");
		return -2;
	}
	int number = 0;
	List* list = createList();
	while (fscanf(file, "%d", &number) > 0) {
		if (insert(list, number) == -1) {
			return -2;
		}
	}
	int result = isSymmetricalList(list);
	clearList(list);
	return result;
}

bool test() {
	int result = workWithFile("test.txt");
	return result == 1;
}

int main() {
	if (test()) {
		printf("Tests correct\n");
	} else {
		printf("Tests incorrect\n");
		return -1;
	}
	char fileName[101] = { '\0' };
	printf("Input fileName, maximum of 100 characters\n");
	int checkScanf = scanf("%s", fileName);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}
		printf("Error...\n");
		checkScanf = scanf("%s", &fileName);
	}
	int result = workWithFile(fileName);
	if (result == -2) {
		printf("Error...\n");
		return -1;
	} else if (result == 1) {
		printf("List symmetrical\n");
	} else {
		printf("List not symmetrical\n");
	}
}