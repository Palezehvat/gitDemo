#include "graph.h"
#include "test.h"
#include <stdlib.h>

bool test() {
	Error errorCheck = ok;
	Graph* graph = createGraph(errorCheck, 6);
	if (errorCheck != ok) {
		return false;
	}
	addRoad(graph, errorCheck, 0, 1, 10);
	if (errorCheck != ok) {
		return false;
	}
	addRoad(graph, errorCheck, 0, 2, 12);
	if (errorCheck != ok) {
		return false;
	}
	addRoad(graph, errorCheck, 1, 3, 10);
	if (errorCheck != ok) {
		return false;
	}
	addRoad(graph, errorCheck, 1, 4, 14);
	if (errorCheck != ok) {
		return false;
	}
	addRoad(graph, errorCheck, 2, 5, 16);
	if (errorCheck != ok) {
		return false;
	}
	addRoad(graph, errorCheck, 3, 5, 21);
	if (errorCheck != ok) {
		return false;
	}
	addCapital(graph, 1, errorCheck);
	if (errorCheck != ok) {
		return false;
	}
	addCapital(graph, 5, errorCheck);
	if (errorCheck != ok) {
		return false;
	}
	toControllTowns(graph, errorCheck);
	if (errorCheck != ok) {
		return false;
	}
	bool** arrayControlledTowns = (bool**)malloc(7 * sizeof(bool*));
	if (arrayControlledTowns == NULL) {
		clearGraph(graph);
		return false;
	}
	for (int i = 0; i < 7; ++i) {
		arrayControlledTowns[i] = calloc(7, sizeof(bool*));
		if (arrayControlledTowns[i] == NULL) {
			for (int j = 0; j < i; ++j) {
				free(arrayControlledTowns[j]);
			}
			free(arrayControlledTowns);
			return false;
		}
	}
	returnArrayWithControlledTowns(graph, errorCheck, arrayControlledTowns);
	if (errorCheck != ok) {
		for (int i = 0; i < 7; ++i) {
			free(arrayControlledTowns[i]);
		}
		free(arrayControlledTowns);
		clearGraph(graph);
		return false;
	}
	return arrayControlledTowns[1][0] && arrayControlledTowns[1][1] && arrayControlledTowns[1][4] 
		&& arrayControlledTowns[1][5] && arrayControlledTowns[5][0] && arrayControlledTowns[5][3];
}