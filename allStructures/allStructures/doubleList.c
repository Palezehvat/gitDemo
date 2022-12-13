#include "doubleList.h"

typedef struct NodeDoubleList {
    const char* value;
    struct NodeDoubleList* next;
    struct NodeDoubleList* prev;
} NodeDoubleList;

typedef struct DoubleList {
    NodeDoubleList* head;
};

DoubleList* createDoubleList(Error* errorCheck) {
    DoubleList* list = calloc(1, sizeof(DoubleList));
    if (list == NULL) {
        *errorCheck = memoryError;
    }
    return list;
}

void addToDoubleList(DoubleList* list, const char* value, Error* errorCheck) {
    if (list == NULL) {
        *errorCheck = emptyPointer;
        return;
    }
    NodeDoubleList* temp = calloc(1, sizeof(NodeDoubleList));
    if (temp == NULL) {
        *errorCheck = memoryError;
        return;
    }

    temp->value = value;
    temp->next = temp;
    temp->prev = temp;
    if (list->head == NULL) {
        list->head = temp;
        return;
    }
    list->head->prev->next = temp;
    temp->prev = list->head->prev;
    temp->next = list->head;
    list->head->prev = temp;
}

bool isEmptyDoubleList(DoubleList* list) {
    if (list == NULL) {
        return true;
    }
    return list->head == NULL;
}

char* deleteElementDoubleList(DoubleList* list, Error* errorCheck) {
    if (list == NULL || list->head == NULL) {
        *errorCheck = emptyPointer;
        return NULL;
    }
    if (list->head->next == list->head) {
        char* value = list->head->value;
        free(list->head);
        list->head = NULL;
        return value;
    }
    char* value = list->head->prev->value;
    NodeDoubleList* temp = list->head->prev->prev;
    free(list->head->prev);
    temp->next = list->head;
    list->head->prev = temp;
    return value;
}

DoubleList* clearDoubleList(DoubleList* list, Error* errorCheck) {
    if (list == NULL) {
        return;
    }

    NodeDoubleList* walkerEnd = list->head->prev; 
    NodeDoubleList* walkerStart = list->head;

    while (walkerEnd != walkerStart && walkerStart->next != walkerEnd) {
        NodeDoubleList* tempStart = walkerStart->next;
        NodeDoubleList* tempEnd = walkerEnd->prev;
        free(walkerStart);
        free(walkerEnd);
        walkerStart = tempStart;
        walkerEnd = tempEnd;
    }
    if (walkerEnd != walkerStart) {
        free(walkerEnd);
    }
    free(walkerStart);
    free(list);
    return NULL;
}