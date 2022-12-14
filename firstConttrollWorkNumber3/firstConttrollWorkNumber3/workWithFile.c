#include "workWithFile.h"

void workWithFile(Error* errorCheck, const char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		*errorCheck = anotherError;
		return;
	}

	Stack* stack = createStack(errorCheck);
	int number = 0;

	while (fscanf(file, "%d", &number) == 1) {
		addElementToStack(stack, errorCheck, number);
		if (*errorCheck != ok) {
			stack = clearStack(stack, errorCheck);
			fclose(file);
			return;
		}
	}
	fclose(file);
	file = fopen(fileName, "w");
	if (file == NULL) {
		*errorCheck = anotherError;
		stack = clearStack(stack, errorCheck);
		return;
	}
	fclose(file);
	file = fopen(fileName, "a");
	while (!isEmpty(stack)) {
		number = deleteElementInStack(stack, errorCheck);
		if (*errorCheck != ok) {
			stack = clearStack(stack, errorCheck);
			fclose(file);
			return;
		}
		fprintf(file, "%d ", number);
	}
	fclose(file);
}