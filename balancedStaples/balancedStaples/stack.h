#ifndef STACK_H_
#define STACK_H_
#include <stdbool.h>

typedef struct ElementStack {
	struct ElementStack* next;
	char value;
} ElementStack;

int pushElements(ElementStack** head, char value);
bool isEmpty(ElementStack* head);
void clear(ElementStack** head);
char popElements(ElementStack** head, int* errorCode);

#endif // !STACK_H_

