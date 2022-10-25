#include "list.h"
#include <stdbool.h>

typedef struct Node {
    int value;
    int position;
    struct Node* next;
} Node;

struct List {
    Node* head;
};

bool isEmpty(List* list) {
    return list->head == NULL;
}

int insert(List* list, int value, int position) {
    Node* currentNode = list->head;
    while (currentNode->position != position) {
        if (currentNode->next == NULL) {
            return -1;
        }
        currentNode = currentNode->next;
    }

    Node* newNode = calloc(1, sizeof(Node));

    newNode->value = value;
    newNode->position = currentNode->position;
    Node* nextNode = currentNode->next;
    newNode->next = nextNode;

    currentNode->next = newNode;
    while (currentNode != NULL) {
        ++currentNode->position;
        currentNode = currentNode->next;
    }
    return 0;
}

void print(List* list) {
    Node* walker = list->head;
    int i = 0;
    while (walker != NULL) {
        printf("%d - %d", i, walker->value);
        ++i;
    }
}

int changeNode(List* list, int position, int value) {
    Node* walker = list->head;
    while (walker->position != position - 1) {
        if (walker->next == NULL) {
            return -1;
        }
        walker = walker->next;
    }
    if (walker->next != NULL) {
        walker->next->value = value;
    }
    return 0;
}

int clear(List* list) {
    int i = 0;
    while (!isEmpty(list)) {
        if (delete(list, i) == -1) {
            return -1;
        }
        ++i;
    }
}

int delete(List* list, int position) {
    if (isEmpty(list)) {
        return -1;
    }
    Node* walker = list->head;
    while (walker->position != position - 1) {
        if (walker->next == NULL) {
            return -1;
        }
        walker = walker->next;
    }
    Node* temp = NULL;
    if (walker->next != NULL) {
        temp = walker->next->next;
        free(walker->next);
        walker->next = temp;
        return 0;
    }
    free(walker->next);
    return 0;
}

int findNode(List* list, int position, int* errorCode) {
    if (isEmpty(list) || position < 0) {
        *errorCode = -1;
        return 0;
    }
    Node* temp = list->head;

    for (int i = 1; i <= position; ++i) {
        temp = temp->next;
        if (temp == NULL) {
            *errorCode = -1;
            return 0;
        }
    }

    return temp->value;

}