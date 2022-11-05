#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Value {
	int number;
	char symbol;
} Value;

typedef struct Node {
    Value value;
    Node* right;
    Node* left;
} Node;

typedef struct Unit {
	Node* value;
	Unit* next;
}Unit;

typedef struct Stack {
	Unit* head;
}Stack;

Stack* createStack(void) {
	Stack* stack = calloc(1, sizeof(stack));
	return stack;
}

int push(Stack* stack, Node* value) {
    Unit* temp = calloc(1, sizeof(Unit));
    if (temp == NULL) {
        printf("Проблемы с памятью...");
        return -1;
    }
    temp->value = value;
    temp->next = stack->head;

    stack->head = temp;
    return 0;
}

Node* pop(Stack* stack, int* errorCode) {
    if (stack->head == NULL) {
        if (errorCode != NULL) {
            *errorCode = -1;
        }
        return NULL;
    }
    if (errorCode != NULL) {
        *errorCode = 0;
    }

    Node* value = stack->head->value;

    Unit* next = stack->head->next;
    free(stack->head);
    stack->head = next;

    return value;
}

bool isEmpty(Stack* stack) {
    return stack->head == NULL;
}

void customDelete(Stack* stack) {
    while (!isEmpty(stack)) {
        int errorCode = 0;
        Node* element = pop(stack, &errorCode);
        free(element);
    }
    free(stack);
    stack = NULL;
}

void deleteStack(Stack* stack) {
    while (!isEmpty(stack)) {
        int errorCode = 0;
        pop(stack, &errorCode);
    }
    free(stack);
    stack = NULL;
}