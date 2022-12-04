#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum Error {
	ok,
	error
}; 

typedef enum Item {
	road,
	notCapital,
	capital
};

typedef struct ValueRoadAndInfoAboutCity {
	bool isExists;
	int sizeRoad;
	enum Item item;
	int controledTown;
} ValueRoadAndInfoAboutCity;

typedef struct AdjacencyMatrix {
	int sizeMatrix;
	struct ValueRoadAndInfoAboutCity** arrayMatrix;
};

AdjacencyMatrix* createMatrix(int sizeMatrix, Error errorCheck) {
	if (sizeMatrix == INT_MAX) {
		errorCheck = error;
		return NULL;
	}
	AdjacencyMatrix* matrix = calloc(sizeMatrix, sizeof(AdjacencyMatrix));
	if (matrix == NULL) {
		errorCheck = error;
		return NULL;
	}
	matrix->arrayMatrix = (ValueRoadAndInfoAboutCity**)malloc(sizeMatrix * sizeof(ValueRoadAndInfoAboutCity*));
	if (matrix->arrayMatrix == NULL) {
		errorCheck = error;
		free(matrix);
		return NULL;
	}
	for (int i = 0; i < sizeMatrix; ++i) {
		matrix->arrayMatrix[i] = (ValueRoadAndInfoAboutCity*)malloc((sizeMatrix + 1) * sizeof(ValueRoadAndInfoAboutCity));
		if (matrix->arrayMatrix[i] == NULL) {
			for (int j = 0; j < i; ++j) {
				free(matrix->arrayMatrix[j]);
			}
			free(matrix);
			errorCheck = error;
			return NULL;
		}
		for (int j = 0; j < sizeMatrix; ++j) {
			matrix->arrayMatrix[i][j].isExists = false;
			matrix->arrayMatrix[i][j].sizeRoad = 0;
			matrix->arrayMatrix[i][j].item = road;
		}
	}
	for (int i = 0; i < sizeMatrix; ++i) {
		matrix->arrayMatrix[i][sizeMatrix].item = notCapital;
		matrix->arrayMatrix[i][sizeMatrix].isExists = false;
		matrix->arrayMatrix[i][sizeMatrix].sizeRoad = 0;
	}
	matrix->sizeMatrix = sizeMatrix;
	return matrix;
}

Error addToCapitalControlledTown(int numberCapital, AdjacencyMatrix* matrix) {
	if (matrix == NULL) {
		return error;
	}
	return ok;
}

Error addRoad(int from, int to, int sizeRoad, AdjacencyMatrix* matrix) {
	if (matrix == NULL || from >= matrix->sizeMatrix || to >= matrix->sizeMatrix) {
		return error;
	}
	matrix->arrayMatrix[from][to].isExists = true;
	matrix->arrayMatrix[from][to].sizeRoad = sizeRoad;
	matrix->arrayMatrix[to][from].isExists = true;
	matrix->arrayMatrix[to][from].sizeRoad = sizeRoad;
	return ok;
}

Error addCapital(int numberCapital, AdjacencyMatrix* matrix) {
	if (matrix == NULL) {
		return error;
	}
	if (numberCapital >= matrix->sizeMatrix) {
		return error;
	}
	matrix->arrayMatrix[numberCapital][matrix->sizeMatrix].item = capital;
	return ok;
}

Error printMatrix(AdjacencyMatrix* matrix) {
	if (matrix == NULL) {
		return  error;
	}
	for (int i = 0; i < matrix->sizeMatrix; ++i) {
		printf("matrix[%2d][] - ", i);
		for (int j = 0; j < matrix->sizeMatrix; ++j) {
			printf("%4d", matrix->arrayMatrix[i][j].sizeRoad);
		}
		printf("\n");
	}
	return ok;
}

AdjacencyMatrix* clearMatrix(AdjacencyMatrix* matrix) {
	if (matrix == NULL) {
		return NULL;
	}
	for (int i = 0; i < matrix->sizeMatrix; ++i) {
		free(matrix->arrayMatrix[i]);
	}
	free(matrix->arrayMatrix);
	free(matrix);
	return NULL;
}