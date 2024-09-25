#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

// �������� ������ �� �������.
bool isEmpty(List* list);

// �������� list'�.
List* createList(void);

// ���������� ������.
int addRecord(List* list, char name[], char number[]);

// ����������.
void mergeSort(int size, List* list, int numberOrName);

// �������� �� �����������������.
bool isSorted(List* list, int numberOrName);

// ������� list'�
void clear(List** list);

// ������ list'�
void printList(List* list);