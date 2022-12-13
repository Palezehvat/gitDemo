#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct NodeStack {
	struct NodeStack* next;
	int value;
} NodeStack;

typedef struct Stack {
	struct NodeStack* head;
}Stack;

Stack* createStack(Error* errorCheck) {
	Stack* stack = calloc(1, sizeof(Stack));
	if (stack == NULL) {
		*errorCheck = memoryError;
		return NULL;
	}
	return stack;
}

void addElementToStack(Stack* stack, Error* errorCheck, int value) {
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