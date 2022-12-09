#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum Error {
	memmoryError,
	anotherError,
	nullGraph,
	outOfGraph,
	fileError,
	ok,
};

Error workWithGraph(const char* fileName) {
	Error errorCheck = ok;
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		return fileError;
	}
	int numberOfTowns = 0;
	if (fscanf(file, "%d", &numberOfTowns) != 1) {
		return fileError;
	}
	Graph* graph = createGraph(errorCheck, numberOfTowns);

	int numberOfRoads = 0;
	if (fscanf(file, "%d", &numberOfRoads) != 1) {
		return fileError;
	}
	int firstTown = 0;
	int secondTown = 0;
	int sizeRoad = 0;
	for (int i = 0; i < numberOfRoads; ++i) {
		if (fscanf(file, "%d %d %d", &firstTown, &secondTown, &sizeRoad) != 3) {
			return fileError;
		}
		addRoad(graph, errorCheck, firstTown, secondTown, sizeRoad);
		if (errorCheck != ok) {
			return errorCheck;
		}
	}
	printGraph(graph);
	return ok;
}

int main() {
	printf("Input fileName, no more than 100 characters\n");
	char fileName[100] = { '\0' };
	char checkScanf = scanf("%s", &fileName);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}
		printf("ERROR\n");
		checkScanf = scanf("%s", &fileName);
	}
	if (workWithGraph(fileName) != ok) {
		printf("Error!\n");
		return -1;
	}
}