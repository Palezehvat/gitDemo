#pragma once
#include <stdbool.h>

typedef struct List List;

typedef enum Error {
	memoryError,
	emptyPointer,
	anotherError,
	ok,
}Error;

List* createList(Error* errorCheck);

bool isEmptyList(List* list);

void addToList(List* list, char value[], Error* errorCheck);

char* deleteElementList(List* list, Error* errorCheck);

List* clearList(List* list, Error* errorCheck);

void addWithASymbolStrings(List* list, Error* errorCheck);

bool isLastElementSame(List* list, char value[], Error* errorCheck);