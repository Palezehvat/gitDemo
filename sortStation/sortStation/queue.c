#include "queue.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int enqueue(Queue* queue, char value[]) {
    Node* temp = calloc(1, sizeof(Node));
    if (temp == NULL) {
        printf("Problems with memory allocation");
        return -1;
    }
    size_t sizeValue = strlen(value);
    memset(temp->value, 0, strlen(temp->value));
    strncpy(temp->value, value, sizeValue);
    temp->next = NULL;

    if (queue->tail == NULL) {
        queue->tail = temp;
        queue->head = temp;
    }
    else {
        queue->tail->next = temp;
        queue->tail = temp;
    }

    return 0;
}

void dequeue(Queue* queue, int* errorCode, char value[]) {
    if (queue->head == NULL) {
        if (errorCode != NULL) {
            *errorCode = -1;
        }

        return 0;
    }
    if (errorCode != NULL) {
        *errorCode = 0;
    }

    size_t sizeQueueHeadValue = strlen(queue->head->value);
    strncpy(value, queue->head->value, sizeQueueHeadValue);

    Node* next = queue->head->next;
    //free(queue->head);
    memset(queue->head->value, 0, strlen(queue->head->value));
    (queue->head)->next = NULL;
    queue->head = NULL;
    queue->head = next;
    if (next == NULL) {
        queue->tail = NULL;
    }
}

bool isEmptyQueue(Queue queue) {
    return queue.head == NULL;
}

void clear(Queue* queue) {
    while (!isEmptyQueue(*queue)) {
        int errorCode = 0;
        dequeue(queue, &errorCode, "");
    }
    queue = NULL;
}