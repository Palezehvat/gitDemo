#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef struct Stack Stack;

typedef struct Node Node;

typedef struct Value Value;

typedef struct Unit Unit;

//�������� stack'a
Stack* createStack(void);

//���������� �������� � ������ �����
int push(Stack* stack, Node* value);

//�������� �������� �� �����(�� ������ �����)
Node* pop(Stack* stack, int* errorCode);

//�������� �� �������
bool isEmpty(Stack* stack);

//������� �����
void deleteStack(Stack* stack);

//������� ����� + ������������� �������� ������ ����
void customDelete(Stack* stack);
#endif