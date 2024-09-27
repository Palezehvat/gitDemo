#pragma once
#include <stdbool.h>

typedef struct Stack Stack;
typedef enum Error Error;

int pushElements(Stack* stack, int value);
bool isEmpty(Stack* stack);
void clear(Stack* stack);
int popElements(Stack* stack, Error checkError);
int top(Stack* stack);