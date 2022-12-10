#pragma once
#include <stdbool.h>

typedef struct Graph Graph;
typedef enum Error {
	memoryError,
	anotherError,
	nullGraph,
	outOfGraph,
	fileError,
	ok,
}Error;

Graph* createGraph(Error errorCheck, int sizeGraph);

void addRoad(Graph* graph, Error errorCheck, int firstNode, int secondNode, int sizeRoad);

void printGraph(Graph* graph);

void toControllTowns(Graph* graph, Error errorCheck);

void addCapital(Graph* graph, int numberCapital, Error checkError);

void returnArrayWithControlledTowns(Graph* graph, Error errorCheck, bool** controlledTownsArray);

void clearGraph(Graph* graph);