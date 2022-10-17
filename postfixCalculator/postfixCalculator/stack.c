#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int pushElements(ElementStack** head, int value) {
	ElementStack* temp = malloc(sizeof(ElementStack));
	if (temp == NULL) {
		return -1;
	}
	temp->value = value;
	temp->next = *head;

	*head = temp;
	return 0;
}

bool isEmpty(ElementStack* head) {
	return head == NULL;
}

void clear(ElementStack** head) {
	while (!isEmpty(*head)) {
		popElements(head, NULL);
	}
}

int popElements(ElementStack** head, int* errorCode) {
	if (*head == NULL && errorCode != NULL) {
		*errorCode = -1;
		return -1;
	}
	*errorCode = 0;

	int value = (*head)->value;

	ElementStack* temp = (*head)->next;
	free(*head);
	*head = temp;
	return value;
}