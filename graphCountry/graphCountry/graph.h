#pragma once

typedef enum Error Error;
typedef struct AdjacencyMatrix AdjacencyMatrix;
typedef struct Graph Graph;

AdjacencyMatrix* createMatrix(int sizeMatrix, Error error);

Error addRoad(int numberCityFrom, int numberCityTo, int sizeRoad, AdjacencyMatrix* matrix);

Error printMatrix(AdjacencyMatrix* matrix);

Error addCapital(int numberCapital, AdjacencyMatrix* matrix);

AdjacencyMatrix* clearMatrix(AdjacencyMatrix* matrix);