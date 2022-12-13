#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DoubleList DoubleList;

typedef enum Error {
	memoryError,
	emptyPointer,
	anotherError,
	ok,
}Error;

DoubleList* createDoubleList(Error* errorCheck);

void addToDoubleList(DoubleList* list, const char* value, Error* errorCheck);

bool isEmptyDoubleList(DoubleList* list);

char* deleteElementDoubleList(DoubleList* list, Error* errorCheck);

DoubleList* clearDoubleList(DoubleList* list, Error* errorCheck);