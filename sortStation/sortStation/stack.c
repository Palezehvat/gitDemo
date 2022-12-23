#include "stack.h"
#include <stdio.h>
#include <malloc.h>

typedef struct Node {
    char value;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* head;
} Stack;

int push(Stack* stack, char value) {
    Node* temp = calloc(1, sizeof(Node));
    if (temp == NULL) {
        printf("Problems with memory allocation");
        return -1;
    }
    temp->value = value;
    temp->next = stack->head;

    stack->head = temp;
    return 0;
}

char pop(Stack* stack, int* errorCode) {
    if (stack->head == NULL) {
        if (errorCode != NULL) {
            *errorCode = -1;
        }

        return 0;
    }
    if (errorCode != NULL) {
        *errorCode = 0;
    }

    char value = stack->head->value;

    Stack* next = stack->head->next;
    free(stack->head);
    stack->head = next;

    return value;
}

bool isEmpty(Stack* stack) {
    return stack->head == NULL;
}

void deleteStack(Stack** stack) {
    while (!isEmpty(*stack)) {
        int errorCode = 0;
        pop(*stack, &errorCode);
    }
    *stack = NULL;
}

Stack* createStack(void) {
    Stack* stack = malloc(sizeof(Stack));
    stack->head = NULL;
    return stack;
}

char top(Stack* stack) {
    if (stack->head == NULL) {
        return "";
    }
    return stack->head->value;
}