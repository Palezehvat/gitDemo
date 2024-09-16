#pragma once
#include <stdbool.h>

typedef struct List List;

//Add elements to list
void insertToList(List* list, char value[], int* errorCode);

//Clear list
void clearList(List* list);

//Delete node in list
void deleteNode(List* list, char value[]);

//create new list
List* createList(int* errorCode);

//Print list
void printList(List* list);

//Is string in List
bool findStringInList(List* list, char value[]);