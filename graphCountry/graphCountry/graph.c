#include "graph.h"
#include "list.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum TypeTown {
	capital,
	notBusy,
	busy
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
	int numberOfCapitals;
}Graph;

Graph* createGraph(Error errorCheck, int sizeGraph) {
	Graph* graph = calloc(1, sizeof(Graph));
	if (graph == NULL) {
		errorCheck = memoryError;
		return NULL;
	}
	graph->numNode = sizeGraph;
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
		graph->nodeList[i][0].onWhichControl = -1;
		graph->nodeList[i][0].typeTown = notBusy;
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
		for (int i = 0; i < graph->numNode; ++i) {
			free(graph->nodeList[i]);
		}
		free(graph);
		return;
	}
	temp->sizeRoadWithMainVertex = sizeRoad;
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
	for (int i = 0; i < graph->numNode; ++i) {
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

void addCapital(Graph* graph, int numberCapital, Error checkError) {
	if (graph == NULL) {
		checkError = anotherError;
		return;
	}

	if (numberCapital >= graph->numNode) {
		checkError = anotherError;
		clearGraph(graph);
		return;
	}

	graph->nodeList[numberCapital]->typeTown = capital;
	Node* walker = graph->nodeList[numberCapital]->next;
	while (walker != NULL) {
		Node* newWalker = graph->nodeList[walker->vertex];
		while (newWalker->vertex != numberCapital) {
			newWalker = newWalker->next;
		}
		newWalker->typeTown = capital;
		walker = walker->next;
	}
	++graph->numberOfCapitals;
}

void recursionAddTown(Graph* graph, int* min, int* numberTown, int index, const int numberCapital, int localMin, Error errorCheck) {
	Node* walker = graph->nodeList[index]->next;
	
	while (walker != NULL) {
		if (walker->typeTown == busy && walker->onWhichControl == numberCapital) {
			localMin += walker->sizeRoadWithMainVertex;
			recursionAddTown(graph, min, numberTown, walker->vertex, numberCapital, localMin, errorCheck);
		} else if (walker->typeTown == notBusy) {
			localMin += walker->sizeRoadWithMainVertex;
			if (localMin < *min || *min == -1) {
				*min = localMin;
				*numberTown = walker->vertex;
			}
			localMin -= walker->sizeRoadWithMainVertex;
		}
		walker = walker->next;
	}

}

void addTown(Graph* graph, int numberCapital, Error errorCheck, bool* isAdded) {
	if (graph == NULL) {
		errorCheck = nullGraph;
		return;
	}
	int min = -1;
	int numberAddedTown = numberCapital;
	int index = numberCapital;
	recursionAddTown(graph, &min, &numberAddedTown, index, numberCapital, 0, errorCheck);
	if (min != -1) {
		graph->nodeList[numberAddedTown]->typeTown = busy;
		graph->nodeList[numberAddedTown]->onWhichControl = numberCapital;
		Node* walker = graph->nodeList[numberAddedTown]->next;
		while (walker != NULL) {
			Node* anotherWalker = graph->nodeList[walker->vertex];
			while (anotherWalker->vertex != numberAddedTown) {
				anotherWalker = anotherWalker->next;
			}
			anotherWalker->typeTown = busy;
			anotherWalker->onWhichControl = numberCapital;
			walker = walker->next;
		}
		*isAdded = true;
	}
}

void toControllTowns(Graph* graph, Error errorCheck) {
	if (graph == NULL) {
		errorCheck = nullGraph;
		return;
	}
	int i = 0;
	int indexCapital = 0;
	bool isAdded = false;
	while (i < graph->numNode - graph->numberOfCapitals) {
		while (graph->nodeList[indexCapital]->typeTown != capital) {
			++indexCapital;
			if (indexCapital == graph->numNode) {
				indexCapital = 0;
			}
		}
		isAdded = false;
		addTown(graph, indexCapital, errorCheck, &isAdded);
		++indexCapital;
		if (indexCapital == graph->numNode) {
			indexCapital = 0;
		}
		if (isAdded) {
			++i;
		}
	}
}

void returnArrayWithControlledTowns(Graph* graph, Error errorCheck, bool** controlledTownsArray) {
	int indexSizeTowns = 0;
	Node* walker = graph->nodeList[0];
	while (indexSizeTowns < graph->numNode) {
		while (walker != NULL) {
			if (walker->typeTown == capital) {
				controlledTownsArray[walker->vertex][0] = true;
			}
			else {
				controlledTownsArray[walker->onWhichControl][walker->vertex + 1] = true;
			}
			walker = walker->next;
		}
		walker = graph->nodeList[indexSizeTowns];
		++indexSizeTowns;
	}
	return controlledTownsArray;
}

void clearGraph(Graph* graph) {
	int i = 0;
	while (i < graph->numNode) {
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