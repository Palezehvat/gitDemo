#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum Error {
	ok,
	error
};

Error workWithGraph(const char* fileName) {
	Error checkError = 0;
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		return error;
	}
	int numberOfRoads = 0;
	if (fscanf(file, "%d", &numberOfRoads) != 1) {
		return error;
	}
	AdjacencyMatrix* matrix = createMatrix(numberOfRoads, checkError);
	if (checkError != ok) {
		return error;
	}
	int numberOfPaths = 0;
	if (fscanf(file, "%d", &numberOfPaths) != 1) {
		matrix = clearMatrix(matrix);
		return error;
	}
	for (int i = 0; i < numberOfPaths; ++i) {
		int to = 0;
		int from = 0;
		int sizeRoad = 0;
		if (fscanf(file, "%d %d %d", &from, &to, &sizeRoad) != 3) {
			matrix = clearMatrix(matrix);
			return error;
		}
		checkError = addRoad(from, to, sizeRoad, matrix);
		if (checkError != ok) {
			matrix = clearMatrix(matrix);
			return error;
		}
	}
	int sizeCapitals = 0;
	if (fscanf(file, "%d", &sizeCapitals) != 1) {
		matrix = clearMatrix(matrix);
		return error;
	}
	int numberCapital = 0;
	for (int i = 0; i < sizeCapitals; ++i) {
		if (fscanf(file, "%d", &numberCapital) != 1) {
			matrix = clearMatrix(matrix);
			return error;
		}
		if (addCapital(numberCapital, matrix) != ok) {
			matrix = clearMatrix(matrix);
			return error;
		}
	}
	fclose(file);
	if (printMatrix(matrix) != ok) {
		matrix = clearMatrix(matrix);
		return error;
	}
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