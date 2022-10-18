#ifndef STACK_H_
#define STACK_H_
#include <stdbool.h>

typedef struct ElementStack {
	struct ElementStack* next;
	int value;
} ElementStack;

int pushElements(ElementStack** head, int value);
bool isEmpty(ElementStack* head);
void clear(ElementStack** head);
int popElements(ElementStack** head, int* errorCode);

#endif // !STACK_H_

