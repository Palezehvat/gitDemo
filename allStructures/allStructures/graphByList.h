#pragma once
#include <stdbool.h>

typedef struct Graph Graph;

typedef enum Error {
	memoryError,
	emptyPointer,
	anotherError,
	ok,
}Error;

Graph* createGraph(Error errorCheck, int sizeGraph);

void addRoad(Graph* graph, Error errorCheck, int firstNode, int secondNode, int sizeRoad);

void printGraph(Graph* graph);

void clearGraph(Graph* graph);