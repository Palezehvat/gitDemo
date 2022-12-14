#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct NodeStack {
	struct NodeStack* next;
	char value;
} NodeStack;

typedef struct Stack {
	struct NodeStack* head;
}Stack;

int createNumberFromStack(Stack* stack, Error* errorCheck) {
	if (stack == NULL) {
		*errorCheck = emptyPointer;
		return;
	}
	NodeStack* walker = stack->head;
	int number = 0;
	int multiplay = 1;

	while (walker != NULL) {
		number += ((int)walker->value - 48)* multiplay;
		multiplay *= 2;
		walker = walker->next;
	}

	return number;
}

Stack* createStack(Error* errorCheck) {
	Stack* stack = calloc(1, sizeof(Stack));
	if (stack == NULL) {
		*errorCheck = memoryError;
		return NULL;
	}
	return stack;
}

void addElementsFromStringToStack(Stack* stack, Error* errorCheck, char value) {
	NodeStack* temp = calloc(1, sizeof(NodeStack));
	if (temp == NULL) {
		*errorCheck = memoryError;
		return;
	}
	temp->value = value;
	temp->next = stack->head;

	stack->head = temp;
	return;
}

void deleteElementInStack(Stack* stack, Error* errorCheck) {
	if (stack == NULL || stack->head == NULL) {
		*errorCheck = anotherError;
		return;
	}
	int value = stack->head->value;
	NodeStack* temp = stack->head->next;
	free(stack->head);
	stack->head = temp;
	return value;
}

Stack* clearStack(Stack* stack, Error* errorCheck) {
	if (stack == NULL) {
		return;
	}
	while (!isEmpty(stack)) {
		deleteElementInStack(stack, errorCheck);
		if (*errorCheck != ok) {
			return stack;
		}
	}
	free(stack);
	return NULL;
}

bool isEmpty(Stack* stack) {
	return stack == NULL ? true : stack->head == NULL;
}