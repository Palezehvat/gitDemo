#pragma once
typedef struct List List;

//Add elements to list
void insertToList(List* list, char value[], int* errorCode);

//Clear list
void clearList(List* list);

//Delete node in list
void deleteNode(List* list, char value[]);

//create new list
List* createList(int* errorCode);