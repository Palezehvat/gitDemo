#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

//Insert to list
int insert(List* list, int value);

bool isEmpty(List* list);

void clearList(List* list);

List* createList(void);

int isSymmetricalList(List* list);