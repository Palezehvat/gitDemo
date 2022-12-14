#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int returnFirstSymbolInNumber(int* number, int sizeNumber) {
	int divide = pow(10, sizeNumber - 1);
	int result = *number / divide;
	*number = *number % divide;
	return result;
}

void workWithFile(Error* errorCheck, const char* fileName, char* numberString) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		*errorCheck = anotherError;
		return -1;
	}

	Stack* stack = createStack(errorCheck);
	char symbol = 0;
	while (fscanf(file, "%c", &symbol) == 1) {
		addElementsFromStringToStack(stack, errorCheck, symbol);
		if (*errorCheck != ok) {
			stack = clearStack(stack, errorCheck);
			fclose(file);
			return;
		}
	}
	fclose(file);
	int sizeNumber = 0;
	int number = createNumberFromStack(stack, errorCheck);
	//MAX_INT - 10 цифр
	int copyNumber = number;
	while (copyNumber != 0) {
		copyNumber /= 10;
		++sizeNumber;
	}

	int i = 0;
	while (number != 0) {
		numberString[i] = returnFirstSymbolInNumber(&number, sizeNumber) + '0';
		--sizeNumber;
		++i;
	}
	free(stack);
	return numberString;
}

bool test() {
	char string[11] = { '\0' };
	Error check = ok;
	workWithFile(&check, "test.txt", string);
	if (check != ok) {
		return false;
	}
	return strcmp(string, "13") == 0;
}

int main() {
	if (test()) {
		printf("Test correct\n");
	} else {
		printf("Error\n");
		return -1;
	}
	printf("Enter fileName with extension No more than 99 symbols\n");
	char fileName[100] = {'\0'};
	int checkScanf = scanf_s("%s", fileName, 99);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}
		checkScanf = scanf_s("%s", fileName, 99);
	}
	Error errorCheck = ok;
	char numberString[11] = { '\0' };
	workWithFile(&errorCheck, fileName, numberString);
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
	printf("%s\n", numberString);
}