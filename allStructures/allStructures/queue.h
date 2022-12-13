#pragma once
#include <stdbool.h>

typedef struct Queue Queue;

typedef enum Error {
	memoryError,
	emptyPointer,
	anotherError,
	ok,
}Error;

void enqueue(Queue* queue, char* value, Error* errorCheck);

char* dequeue(Queue* queue, Error* errorCheck);

bool isEmptyQueue(Queue* queue);

Queue* clearQueue(Queue* queue);

Queue* createQueue(Error* errorCheck);