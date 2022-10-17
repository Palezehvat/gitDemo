#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QueueElement {
	int value;
	struct QueueElement* next;
}QueueElement;

typedef struct Queue {
	struct QueueElement* head;
	struct QueueElement* tail;
}Queue;

int enqueue(Queue* queue, int value) {
	QueueElement* temp = malloc(sizeof(QueueElement));
	if (temp == NULL) {
		printf("Ошибка, потеря памяти");
		return -1;
	}

	temp->value = value;
	temp->next = NULL;

	if (queue->tail == NULL) {
		queue->head = temp;
		queue->tail = temp;
		return 0;
	}

	queue->tail->next = temp;
	queue->tail = temp;

	return 0;
}

int dequeue(Queue* queue, int* errorCode) {
	if (queue->head == NULL){
		if (errorCode != NULL) {
			*errorCode = -1;
			return 0;
		}
	}
	if (errorCode != NULL) {
		*errorCode = 1;
	}

	int value = queue->head->value;

	QueueElement* next = queue->head->next;
	free(queue->head);
	queue->head = next;
	if (queue->head == NULL) {
		queue->tail = NULL;
	}
	return value;
}

bool isEmpty(Queue queue) {
	return queue.head == NULL;
}

void clear(Queue* queue) {
	while (!isEmpty(*queue)) {
		dequeue(queue, NULL);
	}
}

int main() {
	Queue queue = { .head = NULL, .tail = NULL };
	int errorCode = 0;

	if (enqueue(&queue, 100) == -1) {
		printf("Проблемы в программе...\n");
		return -1;
	}
	if (queue.tail == NULL) {
		printf("Проблемы в программе...\n");
		return -1;
	}
	if (enqueue(&queue, 200) == -1) {
		printf("Проблемы в программе...\n");
		return -1;
	}
	if (queue.tail == NULL) {
		printf("Проблемы в программе...\n");
		return -1;
	}
	if (enqueue(&queue, 300) == -1) {
		printf("Проблемы в программе...\n");
		return -1;
	}
	if (queue.tail == NULL) {
		printf("Проблемы в программе...\n");
		return -1;
	}
	if (dequeue(&queue, 300) == -1) {
		printf("Проблемы в программе...\n");
		return -1;
	}
	if (queue.tail == NULL) {
		printf("Проблемы в программе...\n");
		return -1;
	}
	printf("%d", queue.tail->value);
}