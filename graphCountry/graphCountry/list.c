#include "list.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum Error {
	ok,
	error
};

typedef struct Town {
	int numberTown;
	struct Town* nextTown;
	int sizeWay;
}Town;

typedef struct Capital {
	struct Capital* nextCapital;
	struct Town* firstTown;
	int numberCapital;
} Capital;

typedef struct List {
	struct Capital* firstCapital;
} List;

List* createList(Error errorCheck) {
	List* list = calloc(1, sizeof(List));
	if (list == NULL) {
		errorCheck = error;
		return NULL;
	}
	return list;
}

Error addCapitalToList(List* list, int numberCapital) {
	if (list == NULL) {
		return error;
	}
	Capital* temp = calloc(1, sizeof(Capital));
	if (temp == NULL) {
		return error;
	}
	temp->numberCapital = numberCapital;
	temp->firstTown = NULL;
	temp->nextCapital = NULL;
	if (list->firstCapital == NULL) {
		list->firstCapital = temp;
		return ok;
	}
	Capital* walker = list->firstCapital;
	while (walker->nextCapital != NULL) {
		walker = walker->nextCapital;
	}
	walker->nextCapital = temp;
	return ok;
}

void clearList(List* list) {
	if (list == NULL) {
		return;
	}
	
	if (list->firstCapital == NULL) {
		free(list);
		list = NULL;
		return;
	}

	while (list->firstCapital != NULL) {
		Capital* walker = list->firstCapital;
		if (walker->nextCapital == NULL) {
			free(walker->firstTown);
			free(walker);
			free(list);
		}
		while (walker->nextCapital->nextCapital != NULL) {
			walker = walker->nextCapital;
		}
		free(walker->nextCapital->firstTown);
		free(walker->nextCapital);
	}
}

Error addTownToCapital(int numberCapital, int sizeWay, int numberTown, List* list) {
	if (list == NULL) {
		return error;
	}
	Capital* walker = list->firstCapital;
	while (walker != NULL) {
		if (walker->numberCapital == numberCapital) {
			Town* newTown = calloc(1, sizeof(Town));
			if (newTown == NULL) {
				return error;
			}
			newTown->sizeWay = sizeWay;
			newTown->numberTown = numberTown;
			newTown->nextTown = NULL;
			if (walker->firstTown != NULL) {
				Town* temp = walker->firstTown;
				while (temp->nextTown != NULL) {
					temp = temp->nextTown;
				}
				temp->nextTown = newTown;
				return ok;
			}
			walker->firstTown = newTown;		
			return ok;
		}
		walker = walker->nextCapital;
	}
	return error;
}