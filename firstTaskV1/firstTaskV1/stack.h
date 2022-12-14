#pragma once
#include <stdbool.h>

typedef struct Stack Stack;

typedef enum Error {
	memoryError,
	emptyPointer,
	anotherError,
	ok,
}Error;

Stack* createStack(Error* errorCheck);

int createNumberFromStack(Stack* stack, Error* errorCheck);

void addElementsFromStringToStack(Stack* stack, Error* errorCheck, char value);

void deleteElementInStack(Stack* stack, Error* errorCheck);

Stack* clearStack(Stack* stack, Error* errorCheck);

bool isEmpty(Stack* stack);