#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct NodeList {
    const char* value;
    struct NodeList* next;
} NodeList;

typedef struct List {
    NodeList* head;
};

List* createList(Error* errorCheck) {
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCheck = memoryError;
    }
    return list;
}

void addToList(List* list, const char* value, Error* errorCheck) {
    if (list == NULL) {
        *errorCheck = emptyPointer;
        return;
    }
    NodeList* temp = calloc(1, sizeof(NodeList));
    if (temp == NULL) {
        *errorCheck = memoryError;
        return;
    }
    
    temp->value = value;
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