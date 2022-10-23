#pragma once
#include <stdbool.h>

typedef struct Stack Stack;

// Добавление элементов в стек
int push(Stack* stack, char value);

// Удаление элемента стека
char pop(Stack* stack, int* errorCode);

// Проверка на пустоту стека
bool isEmpty(Stack stack);

// Удаление стека
void deleteStack(Stack* stack);

// Создание стека
Stack* createStack(void);

// Возвращает верхний элемент стека
int top(Stack* stack);