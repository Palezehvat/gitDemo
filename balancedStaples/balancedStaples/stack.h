#ifndef STACK_H_
#define STACK_H_
#include <stdbool.h>

typedef struct ElementStack {
	struct ElementStack* next;
	char value;
} ElementStack;

// Добавление элементов. Возвращает 0 если всё хорошо, иначе возвращает -1 если ошибка.
int pushElements(ElementStack** head, char value);

// Проверка на пустой стек.
bool isEmpty(ElementStack* head);

// Очистка стека.
void clear(ElementStack** head);

// Удаление элементов. Возвращает значение, удалённого элемента
char popElements(ElementStack** head, int* errorCode);

#endif // !STACK_H_

