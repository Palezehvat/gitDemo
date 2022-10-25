#include "list.h"
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

struct List {
    Node* head;
};

void print(List* list) {
    Node* walker = list->head;
    while (walker != NULL) {
        printf("%d ", walker->value);
        walker = walker->next;
    }
    printf("\n");
}

bool isEmpty(List* list) {
    return list->head == NULL;
}

int insert(List* list, int value) {
    Node* currentNode = list->head;
    if (currentNode != NULL && currentNode->value >= value) {
        Node* newNode = calloc(1, sizeof(Node));
        if (newNode == NULL) {
            return -1;
        }
        newNode->value = value;
        newNode->next = currentNode;
        list->head = newNode;
        return 0;
    }

    while (currentNode != NULL) {
        if (currentNode->next == NULL || currentNode->next->value >= value) {
            break;
        }
        currentNode = currentNode->next;
    }

    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        return -1;
    }
    newNode->value = value;
    if (currentNode == NULL) {
        list->head = newNode;
        return 0;
    }
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    return 0;
}

void clearList(List* list) {
    while (list->head->next != NULL) {
        Node* walker = list->head;
        while (walker->next != NULL && walker->next->next != NULL) {
            walker = walker->next;
        }
        free(walker->next);
        walker->next = NULL;
    }
    free(list->head->next);
    free(list->head);
    list = NULL;
}

int delete(List* list, int value) {
    Node* currentNode = list->head;

    if (isEmpty(list)) {
        return -1;
    }
    if (currentNode->value == value) {
        Node* temp = currentNode->next;
        free(currentNode);
        list->head = temp;
        return 0;
    }

    while (currentNode != NULL) {
        if (currentNode->next == NULL || currentNode->next->value == value) {
            if (currentNode->next == NULL && currentNode->value != value) {
                return -1;
            }
            break;
        }
        currentNode = currentNode->next;
    }
    
    Node* temp = NULL;
    if (currentNode == NULL) {
        return -1;
    }
    if (currentNode->next != NULL) {
        temp = currentNode->next->next;
        free(currentNode->next);
        currentNode->next = temp;
        return 0;
    }
    free(currentNode->next);
    return 0;
}

List* createList(void) {
    List* list = calloc(1, sizeof(List));
    return list;
}