#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef struct Stack Stack;

typedef struct Node Node;

typedef struct Value Value;

typedef struct Unit Unit;

//Создание stack'a
Stack* createStack(void);

//Добавление элемента в голову стека
int push(Stack* stack, Node* value);

//Удаление элемента из стека(из головы стека)
Node* pop(Stack* stack, int* errorCode);

//Проверка на пустоту
bool isEmpty(Stack* stack);

//Очистка стека
void deleteStack(Stack* stack);
#endif