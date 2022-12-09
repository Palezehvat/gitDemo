#pragma once

typedef struct Graph Graph;
typedef enum Error Error;

Graph* createGraph(Error errorCheck, int sizeGraph);

void addRoad(Graph* graph, Error errorCheck, int firstNode, int secondNode, int sizeRoad);

void printGraph(Graph* graph);