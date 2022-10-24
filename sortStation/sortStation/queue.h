#pragma once
#include <stdbool.h>

typedef struct Node {
    char value[100];
    struct Node* next;
} Node;

typedef struct Queue {
    struct Node* head;
    struct Node* tail;
} Queue;

int enqueue(Queue* queue, char value[]);

char* dequeue(Queue* queue, int* errorCode);

bool isEmptyQueue(Queue queue);

void clear(Queue* queue);