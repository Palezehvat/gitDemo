#include "list.h"
#include "test.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void workWithFile(const char* fileName, Error* errorCheck) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		*errorCheck = anotherError;
		return;
	}
	List* list = createList(errorCheck);
	if (list == NULL) {
		*errorCheck = emptyPointer;
		return;
	}
	char buffer[100] = { '\0' };
	while (fscanf(file, "%s", buffer) == 1) {
		addToList(list, buffer, errorCheck);
		if (*errorCheck != ok) {
			clearList(list, errorCheck);
			return;
		}
	}
	fclose(file);
	addWithASymbolStrings(list, errorCheck);
	if (*errorCheck != ok) {
		clearList(list, errorCheck);
		return;
	}
	clearList(list, errorCheck);
}

int main() {
	if (test()) {
		printf("Tests correct\n");
	}
	else {
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
	Error errorCheck = ok;
	workWithFile(fileName, &errorCheck);
	switch (errorCheck)
	{
	case(ok):
		break;
	case(emptyPointer):
		printf("Error with null pointer\n");
		return -1;
	case(memoryError):
		printf("Error with memory\n");
		return -1;
	case(anotherError):
		printf("Error\n");
		return -1;
	}
}