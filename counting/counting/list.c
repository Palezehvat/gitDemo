#include "list.h"
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int startPosition;
    struct Node* next;
} Node;

struct List {
    Node* head;
};

bool isEmpty(List* list) {
    return list->head == NULL;
}

int top(List* list) {
    if (list->head == NULL) {
        return -1;
    }
    return list->head->startPosition;
}


void addPositions(List* list, int size) {

    int i = 0;
    Node* walker = list->head;
    while (i < size) {
        Node* newNode = calloc(1, sizeof(Node));
        if (newNode == NULL) {
            return NULL;
        }

        if (list->head != NULL) {
            newNode->startPosition = i;
            newNode->next = list->head;
            walker->next = newNode;
            walker = walker->next;
        }
        if (list->head == NULL) {
            newNode->startPosition = i;
            list->head = newNode;
            list->head->next = list->head;
            walker = list->head;
        }
        ++i;
    }
}

List* createList(void) {
    List* list = calloc(1, sizeof(List));
    return list;
}