#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

typedef struct Queue {
    struct Node* head;
    struct Node* tail;
} Queue;

Queue* createQueue(Error* errorCheck) {
    Queue* queue = calloc(1, sizeof(Queue));
    if (queue == NULL) {
        *errorCheck = memoryError;
    }
    return queue;
}

void enqueue(Queue* queue, char* value, Error *errorCheck) {
    Node* temp = calloc(1, sizeof(Node));
    if (temp == NULL) {
        *errorCheck = memoryError;
        return ;
    }
    temp->value = value;
    temp->next = NULL;

    if (queue->tail == NULL) {
        queue->tail = temp;
        queue->head = temp;
    }
    else {
        queue->tail->next = temp;
        queue->tail = temp;
    }

    return ;
}

char* dequeue(Queue* queue, Error* errorCheck) {
    if (queue == NULL || queue->head == NULL) {
        *errorCheck = emptyPointer;
        return;
    }

    char* value = queue->head->value;
    Node* next = queue->head->next;
    free(queue->head);
    queue->head = next;
    if (next == NULL) {
        queue->tail = NULL;
    }
    return value;
}

bool isEmptyQueue(Queue* queue) {
    if (queue == NULL) {
        return true;
    }
    return queue->head == NULL;
}

Queue* clearQueue(Queue* queue) {
    if (queue == NULL) {
        return NULL;
    }

    while (!isEmptyQueue(queue)) {
        int errorCode = 0;
        Error errorCheck = ok;
        char* value = dequeue(queue, &errorCheck);
        free(value);
    }
    free(queue);
    return NULL;
}