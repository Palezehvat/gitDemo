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

// Очистка списка, поправить работу

void addPositions(List* list, int size) {
    int i = 0;
    Node* walker = list->head;
    while (i < size) {
        Node* newNode = calloc(1, sizeof(Node));
        if (newNode == NULL) {
            return NULL;
        }

        newNode->startPosition = i;

        if (list->head != NULL) {
            newNode->next = list->head;
            walker->next = newNode;
            walker = walker->next;
        } else {
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

int counting(List* list, int size, int step) {
    int newStep = step % size;
    Node* walker = list->head;
    int i = 0;
    Node* walkerNewNext = NULL;
    while (list->head != NULL && list->head->next != list->head) {
        int i = 0;
        while (i < newStep - 1) {
            walker = walker->next;
            ++i;
        }
        if (walker->next == NULL) {
            return -1;
        }
        walkerNewNext = walker->next->next;
        if (list->head == walker->next) {
            list->head = walkerNewNext;
        }
        free(walker->next);
        walker->next = walkerNewNext;
    }
    if (list->head == NULL) {
        return -1;
    }
    int result = list->head->startPosition;
    free(list->head);
    return result;
}
