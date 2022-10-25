#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

int insert(List* list, int value);

void print(List* list);

int delete(List* list, int value);

bool isEmpty(List* list);

void clearList(List* list);

List* createList(void);