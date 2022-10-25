#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

int insert(List* list, int value, int position);

void print(List* list);

int delete(List* list, int position);

int changeNode(List* list, int position, int value);

bool isEmpty(List* list);

int clear(List* list);

int findNode(List* list, int position, int* errorCode);
