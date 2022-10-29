#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

bool isEmpty(List* list);

List* createList(void);

int addRecord(List* list, char name[], char number[]);

void mergeSort(int with, int to, List* list, List* listCopy, int numberOrName);

bool isSorted(List* list, int numberOrName);

void clear(List* list);

void printList(List* list);