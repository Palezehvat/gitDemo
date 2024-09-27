#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum Error {
	ok,
	error
}Error;

typedef struct ElementStack {
	struct ElementStack* next;
	int value;
} ElementStack;

typedef struct Stack {
	struct ElementStack* head;
}Stack;

int pushElements(Stack* stack, int value) {
	ElementStack* temp = malloc(sizeof(ElementStack));
	if (temp == NULL) {
		return -1;
	}
	temp->value = value;
	temp->next = stack;

	stack = temp;
	return 0;
}

bool isEmpty(Stack* stack) {
	return stack == NULL || stack->head == NULL;
}

void clear(Stack* stack) {
	if (stack == NULL) {
		return;
	}
	while (!isEmpty(stack)) {
		popElements(stack, NULL);
	}
}

int popElements(Stack* stack, Error checkError) {
	if (stack == NULL || stack->head) {
		checkError = error;
		return -1;
	}

	int value = stack->head->value;

	ElementStack* temp = stack->head->next;
	free(stack->head);
	stack->head = temp;

	return value;
}

int top(Stack* stack) {
	if (stack == NULL || stack->head == NULL) {
		return -1;
	}
	return stack->head->value;
}