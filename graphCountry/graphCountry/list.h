#pragma once

typedef struct List List;
typedef enum Error Error;

List* createList(Error errorCheck);

Error addCapitalToList(List* list, int numberCapital);

void clearList(List* list);

Error addTownToCapital(int numberCapital, int sizeWay, int numberTown, List* list);