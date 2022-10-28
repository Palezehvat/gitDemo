#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

bool isEmpty(List* list);

List* createList(void);

int top(List* list);

void addPositions(List* list, int size);

int counting(List* list, int size, int step);