#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    char value[100];
    int size;
    struct Node* next;
} Node;

typedef struct List {
    struct Node* head;
};

Node* newNode(int* errorCode, char value[]) {
    Node* temp = calloc(1, sizeof(Node));
    if (temp == NULL) {
        *errorCode = -1;
        return NULL;
    }
    strcpy(temp->value, value);
    ++temp->size;
    return temp;
}

void insertToList(List* list, char value[], int *errorCode) {
    if (list == NULL) {
        *errorCode = -1;
        return;
    }
    if (list->head == NULL) {
        list->head = newNode(errorCode, value);
        return;
    }
    Node* walker = list->head;
    while (walker->next != NULL) {
        if (strcmp(walker->value, value) == 0) {
            ++walker->size;
            return;
        }
        walker = walker->next;
    }
    if (strcmp(walker->value, value) == 0) {
        ++walker->size;
        return;
    }
    walker->next = newNode(errorCode, value);
}

void helpedClearList(Node* element) {
    if (element) {
        helpedClearList(element->next);
        free(element);
    }
}

void clearList(List* list) {
    if (list == NULL) {
        return;
    }
    helpedClearList(list->head);
    free(list);
    list = NULL;
    return;
}

void deleteNode(List* list, char value[]) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    if (strcmp(value, list->head->value) == 0) {
        Node* temp = list->head->next;
        free(list->head);
        list->head = temp;
        return;
    }
    Node* walker = list->head;
    while (walker->next != NULL && strcmp(walker->next->value, value) != 0) {
        walker = walker->next;
    }
    if (walker->next != NULL) {
        free(walker->next);
        walker->next = NULL;
    }
}

List* createList(int *errorCode) {
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = -1;
        return NULL;
    }
    list->head = NULL;
    return list;
}

void printList(List* list) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    Node* walker = list->head;
    int i = 0;
    while (walker != NULL) {
        printf("\n%d: %s -- %d", i, walker->value, walker->size);
        walker = walker->next;
        ++i;
    }
    printf("\n");
}

bool findStringInList(List* list, char value[]) {
    if (list == NULL) {
        return false;
    }
    Node* walker = list->head;
    while (walker != NULL) {
        if (strcmp(walker->value, value) == 0) {
            return true;
        }
        walker = walker->next;
    }
    return false;
}