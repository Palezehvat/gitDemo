#include "graph.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Error workWithGraph(const char* fileName) {
	Error errorCheck = ok;
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		return fileError;
	}
	int numberOfTowns = 0;
	if (fscanf_s(file, "%d", &numberOfTowns) != 1) {
		fclose(file);
		return fileError;
	}
	if (numberOfTowns == INT_MAX) {
		return anotherError;
	}
	Graph* graph = createGraph(errorCheck, numberOfTowns);

	int numberOfRoads = 0;
	if (fscanf_s(file, "%d", &numberOfRoads) != 1) {
		fclose(file);
		return fileError;
	}
	int firstTown = 0;
	int secondTown = 0;
	int sizeRoad = 0;
	for (int i = 0; i < numberOfRoads; ++i) {
		if (fscanf_s(file, "%d %d %d", &firstTown, &secondTown, &sizeRoad) != 3) {
			fclose(file);
			return fileError;
		}
		addRoad(graph, errorCheck, firstTown, secondTown, sizeRoad);
		if (errorCheck != ok) {
			clearGraph(graph);
			fclose(file);
			return errorCheck;
		}
	}
	int numberOfCapitals = 0;
	if (fscanf_s(file, "%d", &numberOfCapitals) != 1) {
		clearGraph(graph);
		fclose(file);
		return fileError;
	}
	int numberCapital;
	for (int i = 0; i < numberOfCapitals; ++i) {
		if (fscanf_s(file, "%d", &numberCapital) != 1){
			clearGraph(graph);
			fclose(file);
			return fileError;
		}
		addCapital(graph, numberCapital, errorCheck);
	}
	fclose(file);
	toControllTowns(graph, errorCheck);
	if (errorCheck != ok) {
		clearGraph(graph);
		return errorCheck;
	}
	int sizeArray = 0;
	bool** arrayControlledTowns = (bool**)malloc((numberOfTowns + 1) * sizeof(bool*));
	if (arrayControlledTowns == NULL) {
		clearGraph(graph);
		return memoryError;
	}
	for (int i = 0; i < numberOfTowns + 1; ++i) {
		arrayControlledTowns[i] = calloc((numberOfTowns + 1),sizeof(bool*));
		if (arrayControlledTowns[i] == NULL) {
			for (int j = 0; j < i; ++j) {
				free(arrayControlledTowns[j]);
			}
			free(arrayControlledTowns);
			clearGraph(graph);
			return memoryError;
		}
	}
	returnArrayWithControlledTowns(graph, errorCheck, arrayControlledTowns);
	if (errorCheck != ok) {
		for (int i = 0; i < numberOfTowns + 1; ++i) {
			free(arrayControlledTowns[i]);
		}
		free(arrayControlledTowns);
		clearGraph(graph);
		return errorCheck;
	}
	
	for (int i = 0; i < numberOfTowns + 1; ++i) {
		if (arrayControlledTowns[i][0]) {
			printf("%d: ", i);
			for (int j = 1; j < numberOfTowns + 1; ++j) {
				if (arrayControlledTowns[i][j]) {
					printf("%d ", j - 1);
				}
			}
			printf("\n");
		}
	}
	for (int i = 0; i < numberOfTowns + 1; ++i) {
		free(arrayControlledTowns[i]);
	}
	free(arrayControlledTowns);
	clearGraph(graph);
	return ok;
}

int main() {
	if (test()) {
		printf("Tests correct!\n");
	} else {
		printf("Error!\n");
		return -1;
	}
	printf("Input fileName, no more than 100 characters\n");
	char fileName[100] = { '\0' };
	char checkScanf = scanf_s("%s", &fileName, 99);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}
		printf("ERROR\n");
		checkScanf = scanf_s("%s", &fileName, 99);
	}
	Error errorCheck = workWithGraph(fileName);
	switch (errorCheck)
	{
	case(ok):
		return 0;
	case(memoryError):
		printf("Error with memory\n");
		return -1;
	case(anotherError):
		printf("Error\n");
		return -1;
	case(nullGraph):
		printf("Error with null graph\n");
		return -1;
	case(outOfGraph):
		printf("Error going beyond the graph\n");
		return -1;
	case(fileError):
		printf("Error with file\n");
		return -1;
	}
}