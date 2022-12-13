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

void addToList(List* list, const char* value, Error* errorCheck);

char* deleteElementList(List* list, Error* errorCheck);

List* clearList(List* list, Error* errorCheck);