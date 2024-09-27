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
            clearList(&list);
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

int counting(List** list, int size, int step) {
    int newStep = step % size;
    Node* walker = (*list)->head;
    int i = 0;
    Node* walkerNewNext = NULL;
    while ((*list)->head != NULL && (*list)->head->next != (*list)->head) {
        int i = 0;
        while (i < newStep - 2) {
            walker = walker->next;
            ++i;
        }
        if (walker->next == NULL || walker->next->next == NULL) {
            clearList(list);
            return -1;
        }
        walkerNewNext = walker->next->next;
        if ((*list)->head == walker->next) {
            (*list)->head = walkerNewNext;
        }
        free(walker->next);
        walker->next = walkerNewNext;
    }
    if ((*list)->head == NULL) {
        free(*list);
        return -1;
    }
    int result = (*list)->head->startPosition;
    free((*list)->head);
    free(*list);
    *list = NULL;
    return result;
}

void clearList(List** list) {
    while ((*list)->head != (*list)->head->next) {
        Node* prevWalker = (*list)->head;
        (*list)->head = (*list)->head->next;
        free(prevWalker);
    }
    free((*list)->head);
    free(*list);
    *list = NULL;
}