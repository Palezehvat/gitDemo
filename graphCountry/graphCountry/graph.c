#include "graph.h"
#include "list.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum Error {
	memmoryError,
	anotherError,
	nullGraph,
	outOfGraph,
	fileError,
	ok,
};

typedef enum TypeTown {
	capital,
	notBusy,
	Busy
}TypeTown;

typedef struct Node {
	int vertex;
	TypeTown typeTown;
	int onWhichControl;
	struct Node* next;
	int sizeRoadWithMainVertex;
}Node;

typedef struct Graph {
	int numNode;
	struct Node** nodeList;
}Graph;

Graph* createGraph(Error errorCheck, int sizeGraph) {
	Graph* graph = calloc(1, sizeof(Graph));
	if (graph == NULL) {
		errorCheck = memmoryError;
		return NULL;
	}
	graph->numNode = sizeGraph;
	graph->nodeList = (Node**)malloc(sizeGraph * sizeof(Node));
	if (graph->nodeList == NULL) {
		errorCheck = memmoryError;
		free(graph);
		return NULL;
	}
	for (int i = 0; i < sizeGraph; ++i) {
		graph->nodeList[i] = calloc(1, sizeof(Node*));
		if (graph->nodeList[i] == NULL) {
			errorCheck = memmoryError;
			for (int j = 0; j < i; ++j) {
				free(graph->nodeList[j]);
			}
			free(graph);
			return NULL;
		}
		graph->nodeList[i][0].vertex = i;
		graph->nodeList[i][0].next = NULL;
		graph->nodeList[i][0].onWhichControl = -1;
		graph->nodeList[i][0].typeTown = notBusy;
	}

	return graph;
}

void helpToAddRoad(Graph* graph, int firstNode, int secondNode, int sizeRoad, Error errorCheck) {
	Node* walkerInGraph = graph->nodeList[firstNode];
	while (walkerInGraph->next != NULL) {
		walkerInGraph = walkerInGraph->next;
	}
	Node* temp = calloc(1, sizeof(Node));
	if (temp == NULL) {
		errorCheck = memmoryError;
		for (int i = 0; i < graph->numNode; ++i) {
			free(graph->nodeList[i]);
		}
		free(graph);
		return;
	}
	walkerInGraph->sizeRoadWithMainVertex = sizeRoad;
	temp->vertex = secondNode;
	temp->next = NULL;
	temp->onWhichControl = -1;
	temp->typeTown = notBusy;
	walkerInGraph->next = temp;
}

void addRoad(Graph* graph, Error errorCheck, int firstNode, int secondNode, int sizeRoad) {
	if (graph == NULL) {
		errorCheck = nullGraph;
		return;
	}
	if (firstNode >= graph->numNode || secondNode >= graph->numNode) {
		errorCheck = outOfGraph;
		for (int i = 0; i < graph->numNode; ++i) {
			free(graph->nodeList[i]);
		}
		free(graph);
		return;
	}
	helpToAddRoad(graph, firstNode, secondNode, sizeRoad, errorCheck);
	if (errorCheck != ok) {
		return;
	}

	if (firstNode != secondNode) {
		helpToAddRoad(graph, secondNode, firstNode, sizeRoad, errorCheck);
		if (errorCheck != ok) {
			return;
		}
	}
}

void printGraph(Graph* graph) {
	if (graph == NULL) {
		return;
	}
	for (int i = 0; i < graph->numNode; ++i) {
		Node* walker = graph->nodeList[i];
		printf("%d: ", walker->vertex);
		if (walker->next != NULL) {
			printf("-%d- ", walker->sizeRoadWithMainVertex);
		}
		walker = walker->next;
		while (walker != NULL) {
			printf("%d ", walker->vertex); if (walker->next != NULL) {
				printf("-%d- ", walker->sizeRoadWithMainVertex);
			}
			walker = walker->next;
		}
		printf("\n");
	}
}

void addCapital(Graph* graph, int numberCapital, Error checkError) {
	if (numberCapital >= graph->numNode) {
		checkError = anotherError;
		return;
	}
	if (graph == NULL) {
		checkError = anotherError;
		return;
	}
	graph->nodeList[numberCapital]->typeTown = capital;
}

void recursionAddTown(Graph* graph, int* min, int* numberTown) {
	{

	}
}

void addTown(Graph* graph, int numberTown) {
	int min = -1;
	int numberAddedTown = -1;
	recursionAddTown(graph, &min, &numberTown);
}