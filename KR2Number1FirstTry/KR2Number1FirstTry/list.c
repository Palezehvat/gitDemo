#include "list.h"
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

struct List {
    struct Node* head;
    struct Node* tail;
};

int insert(List* list, int value) {
    if (list->head == NULL) {
        Node* temp = calloc(1, sizeof(Node));
        if (temp == NULL) {
            return -1;
        }
        list->head = temp;
        list->tail = temp;
        temp->next = temp;
        temp->prev = temp;
        temp->value = value;
        return 0;
    }

    Node* walker = list->head;
    while (walker->next != list->head) {
        walker = walker->next;
    }
    Node* temp = calloc(1, sizeof(Node));
    if (temp == NULL) {
        return -1;
    }
    temp->value = value;
    list->tail = temp;
    walker->next = temp;
    temp->prev = walker;
    temp->next = list->head;
    return 0;
}

void clearList(List* list) {
    if (list->head == NULL) {
        free(list);
        return;
    }
    while (list->head != list->tail) {
        Node* walker = list->head;
        while (walker != list->tail) {
            walker = walker->next;
        }
        list->tail = walker->prev;
        free(walker);
        walker = NULL;
    }
    free(list->head);
    free(list);
}

List* createList(void) {
    List* list = calloc(1, sizeof(List));
    return list;
}

int isSymmetricalList(List* list) {
    if (list == NULL || list->head == list->tail) {
        return 1;
    }
    Node* walkerHead = list->head;
    Node* walkerTail = list->tail;
    while (walkerTail != list->head && walkerHead != list->tail) {
        if (walkerTail->value != walkerHead->value) {
            return 0;
        }
        walkerHead = walkerHead->next;
        walkerTail = walkerTail->prev;
    }
    return 1;
}