#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct NodeList {
    char value[100];
    struct NodeList* next;
} NodeList;

typedef struct List {
    NodeList* head;
};

bool isLastElementSame(List* list, char value[], Error* errorCheck) {
    if (list == NULL || list->head == NULL) {
        *errorCheck = emptyPointer;
        return false;
    }
    NodeList* walker = list->head;
    while (walker->next != NULL) {
        walker = walker->next;
    }
    return strcmp(walker->value, value) == 0;
}

List* createList(Error* errorCheck) {
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCheck = memoryError;
    }
    return list;
}

int sizeList(List* list) {
    int sizeList = 0;
    NodeList* walker = list->head;
    while (walker != NULL) {
        ++sizeList;
        walker = walker->next;
    }
    return sizeList;
}

void addWithASymbolStrings(List* list, Error* errorCheck) {
    if (list == NULL) {
        *errorCheck = emptyPointer;
        return;
    }
    NodeList* walker = list->head;
    int size = sizeList(list);
    int i = 0;
    while (i < size && walker != NULL) {
        if (walker->value != NULL && walker->value[0] == 'a') {
            addToList(list, walker->value, errorCheck);
            if (errorCheck != ok) {
                return;
            }
        }
        walker = walker->next;
        ++i;
    }
}

void addToList(List* list, char value[], Error* errorCheck) {
    if (list == NULL) {
        *errorCheck = emptyPointer;
        return;
    }
    NodeList* temp = calloc(1, sizeof(NodeList));
    if (temp == NULL) {
        *errorCheck = memoryError;
        return;
    }

    strcpy(temp->value, value);
    temp->next = NULL;

    if (list->head == NULL) {
        list->head = temp;
        return;
    }
    NodeList* walker = list->head;
    while (walker->next != NULL) {
        walker = walker->next;
    }
    walker->next = temp;
}

bool isEmptyList(List* list) {
    if (list == NULL) {
        return true;
    }
    return list->head == NULL;
}

char* deleteElementList(List* list, Error* errorCheck) {
    if (list == NULL || list->head == NULL) {
        *errorCheck = emptyPointer;
        return NULL;
    }
    if (list->head->next == NULL) {
        char* value = list->head->value;
        free(list->head);
        list->head = NULL;
        return value;
    }
    NodeList* walker = list->head;
    while (walker->next->next != NULL) {
        walker = walker->next;
    }
    char* value = walker->next->value;
    free(walker->next);
    walker->next = NULL;
    return value;
}

List* clearList(List* list, Error* errorCheck) {
    if (list == NULL) {
        return;
    }

    while (!isEmptyList(list)) {
        deleteElementList(list, errorCheck);
    }

    free(list);
    return NULL;
}