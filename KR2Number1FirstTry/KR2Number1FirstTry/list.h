#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

//Insert to list
int insert(List* list, int value);

//Clear list
void clearList(List* list);

//Create new list
List* createList(void);

//Check is symmetrical list
int isSymmetricalList(List* list);