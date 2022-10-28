#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

bool isEmpty(List* list);

List* createList(void);

int addRecord(List* list, char name[], char number[]);

void mergeSortByName(List* list, int size);

void mergeSortByNumber(List* list, int size);

bool isSortedByNumber(List* list);