#include "graphByList.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
	int vertex;
	struct Node* next;
	int sizeRoadWithMainVertex;
}Node;

typedef struct Graph {
	int sizeGraph;
	struct Node** nodeList;
}Graph;

Graph* createGraph(Error errorCheck, int sizeGraph) {
	Graph* graph = calloc(1, sizeof(Graph));
	if (graph == NULL) {
		errorCheck = memoryError;
		return NULL;
	}
	graph->sizeGraph = sizeGraph;
	graph->nodeList = (Node**)malloc(sizeGraph * sizeof(Node));
	if (graph->nodeList == NULL) {
		errorCheck = memoryError;
		free(graph);
		return NULL;
	}
	for (int i = 0; i < sizeGraph; ++i) {
		graph->nodeList[i] = calloc(1, sizeof(Node*));
		if (graph->nodeList[i] == NULL) {
			errorCheck = memoryError;
			for (int j = 0; j < i; ++j) {
				free(graph->nodeList[j]);
			}
			free(graph);
			return NULL;
		}
		graph->nodeList[i][0].vertex = i;
		graph->nodeList[i][0].next = NULL;
		graph->nodeList[i][0].sizeRoadWithMainVertex = 0;
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
		errorCheck = memoryError;
		for (int i = 0; i < graph->sizeGraph; ++i) {
			free(graph->nodeList[i]);
		}
		free(graph);
		return;
	}
	temp->sizeRoadWithMainVertex = sizeRoad;
	temp->vertex = secondNode;
	temp->next = NULL;
	walkerInGraph->next = temp;
}

void addRoad(Graph* graph, Error errorCheck, int firstNode, int secondNode, int sizeRoad) {
	if (graph == NULL) {
		errorCheck = emptyPointer;
		return;
	}

	if (firstNode >= graph->sizeGraph || secondNode >= graph->sizeGraph) {
		errorCheck = anotherError;
		for (int i = 0; i < graph->sizeGraph; ++i) {
			free(graph->nodeList[i]);
		}
		free(graph);
		return;
	}

	if (firstNode == secondNode) {
		graph->nodeList[firstNode]->sizeRoadWithMainVertex = sizeRoad;
		return;
	}

	helpToAddRoad(graph, firstNode, secondNode, sizeRoad, errorCheck);
	if (errorCheck != ok) {
		clearGraph(graph);
		return;
	}

	if (firstNode != secondNode) {
		helpToAddRoad(graph, secondNode, firstNode, sizeRoad, errorCheck);
		if (errorCheck != ok) {
			clearGraph(graph);
			return;
		}
	}
}

void printGraph(Graph* graph) {
	if (graph == NULL) {
		return;
	}
	for (int i = 0; i < graph->sizeGraph; ++i) {
		Node* walker = graph->nodeList[i];
		printf("%d : ", walker->vertex);
		if (walker->sizeRoadWithMainVertex != 0) {
			printf("-%d- ", walker->sizeRoadWithMainVertex);
		}
		walker = walker->next;
		while (walker != NULL) {
			printf("%d ", walker->vertex);
			printf("(%d) ", walker->sizeRoadWithMainVertex);
			walker = walker->next;
		}
		printf("\n");
	}
}

void clearGraph(Graph* graph) {
	int i = 0;
	while (i < graph->sizeGraph) {
		Node* walker = graph->nodeList[i]->next;
		while (walker != NULL) {
			Node* temp = walker->next;
			free(walker);
			walker = temp;
		}
		//		free(graph->nodeList[i]);
		++i;
	}
	free(graph->nodeList);
	free(graph);
}