#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include <string.h>
#include <locale.h>

bool converterToPostfixForm(const char buffer[], char result[]) {
	size_t sizeBuffer = strlen(buffer);
	Queue queue = { NULL, NULL };
	Stack* operatorActions = createStack();
	size_t i = 0;
	int errorCode = 0;
	char number[100] = { '\0' };
	while (i < sizeBuffer) {
		memset(number, 0, strlen(number));
		int walker = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9') {
			number[walker] = buffer[i];
			++i;
			++walker;
		}
		if (strlen(number) != 0) {
			enqueue(&queue, number);
		}
		if (buffer[i] == '*' || buffer[i] == '+' || buffer[i] == '/' || buffer[i] == '-' || buffer[i] == '(' || buffer[i] == ')') {
			if (isEmpty(operatorActions)) {
				push(operatorActions, buffer[i]);
			}
			else if (buffer[i] == '(') {
				push(operatorActions, buffer[i]);
			}
			else if (top(operatorActions) == '(') {
				push(operatorActions, buffer[i]);
			}
			else if (buffer[i] == ')') {
				while (!isEmpty(operatorActions)) {
					char operations = pop(operatorActions, &errorCode);
					char symbol[2] = { '\0' };
					symbol[0] = operations;
					if (errorCode != 0) {
						return false;
					}
					if (operations != '(') {
						enqueue(&queue, symbol);
					}
				}
			}
			else if (buffer[i] == '*' || buffer[i] == '/') {
				if (top(operatorActions) == '/' || top(operatorActions) == '*') {
					while (!isEmpty(operatorActions) && (top(operatorActions) == '/' || top(operatorActions) == '*')) {
						char operations = pop(operatorActions, &errorCode);
						char symbol[2] = { '\0' };
						symbol[0] = operations;
						if (errorCode != 0) {
							return false;
						}
						if (operations != '(') {
							enqueue(&queue, symbol);
						}
					}
				}
				push(operatorActions, buffer[i]);
			}
			else if (buffer[i] == '+' || buffer[i] == '-') {
				while (!isEmpty(operatorActions)) {
					char operations = pop(operatorActions, &errorCode);
					char symbol[2] = { '\0' };
					symbol[0] = operations;
					if (errorCode != 0) {
						return false;
					}
					if (operations != '(') {
						enqueue(&queue, symbol);
					}
				}
				push(operatorActions, buffer[i]);
			}
		}
		++i;
	}
	while (!isEmpty(operatorActions)) {
		char operations = pop(operatorActions, &errorCode);
		if (errorCode != 0) {
			return false;
		}
		char symbol[2] = { '\0' };
		symbol[0] = operations;
		if (operations != '(') {
			enqueue(&queue, symbol);
		}
	}
	size_t j = 0;
	while (!isEmptyQueue(queue)) {
		char queueElements[100] = { '\0' };
		dequeue(&queue, &errorCode, queueElements);
		if (errorCode != 0) {
			return false;
		}
		size_t sizeQueueElements = strlen(queueElements);
		size_t i = 0;
		while (i < sizeQueueElements) {
			result[j] = queueElements[i];
			++i;
			++j;
		}
		result[j] = ' ';
		++j;
	}
	if (!isEmptyQueue(queue)) {
		clear(&queue);
		return false;
	}
	if (operatorActions != NULL) {
		if (!isEmpty(operatorActions)) {
			deleteStack(operatorActions);
			return false;
		}
		deleteStack(operatorActions);
	}
	return true;
}

bool firstTest() {
	char buffer[12] = { '(', '1', ' ', '+', ' ', '2', ')', ' ', '*', ' ', '2', '\0' };
	char arrayOutput[100] = { '\0' };
	if (!converterToPostfixForm(buffer, arrayOutput)) {
		return false;
	}
	char bufferNew[10] = { '1', ' ', '2', ' ', '+', ' ', '2', ' ', '*', '\0' };
	size_t sizeArrayOutput = strlen(arrayOutput);

	for (int i = 0; i < sizeArrayOutput - 1; ++i) {
		if (bufferNew[i] != arrayOutput[i]) {
			return false;
		}
	}
	return true;
}

bool secondTest() {
	char buffer[18] = { '(', '1', ' ', '+', ' ', '2', ')', ' ', '*', ' ', '(', '1', ' ', '+', ' ', '2', ')', '\0' };
	char arrayOutput[100] = { '\0' };
	if (!converterToPostfixForm(buffer, arrayOutput)) {
		return false;
	}
	char bufferNew[14] = { '1', ' ', '2', ' ', '+', ' ', '1', ' ', '2', ' ', '+', ' ', '*', '\0' };
	size_t sizeArrayOutput = strlen(arrayOutput);

	for (int i = 0; i < sizeArrayOutput - 1; ++i) {
		if (bufferNew[i] != arrayOutput[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	setlocale(LC_ALL, "RUS");

	if (firstTest() && secondTest()) {
		printf("Тесты прошли успешно\n");
	} else {
		printf("Тесты провалились...\n");
	}

	printf("Введите строку примера в итеративной форме\n");
	char buffer[100] = { '\0' };
	gets_s(buffer, 100);
	char result[100] = { '\0' };
	if (converterToPostfixForm(buffer, result)) {
		printf("%s", result);
	} else {
		printf("Произошла ошибка...\n");
	}
}