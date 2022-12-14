#include "stack.h"
#include "test.h"
#include "workWithFile.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	if (test()) {
		printf("Test correct\n");
	}
	else {
		printf("Error\n");
		return -1;
	}
	printf("Enter fileName with extension No more than 99 symbols\n");
	char fileName[100] = { '\0' };
	int checkScanf = scanf_s("%s", fileName, 99);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}
		checkScanf = scanf_s("%s", fileName, 99);
	}
	Error errorCheck = ok;
	workWithFile(&errorCheck, fileName, fileName);
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