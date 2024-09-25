#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

// Проверка списка на пустоту.
bool isEmpty(List* list);

// Создание list'а.
List* createList(void);

// Добавление записи.
int addRecord(List* list, char name[], char number[]);

// Сортировка.
void mergeSort(int size, List* list, int numberOrName);

// Проверка на отсортированность.
bool isSorted(List* list, int numberOrName);

// Очистка list'а
void clear(List** list);

// Печать list'а
void printList(List* list);