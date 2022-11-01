#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "binaryTree.h"
#include <string.h>

int scanOne();

bool talkWithUser(void) {
	printf("Введите одну из следующих команд\n0 - Выход из интерактивного меню.\n1 - Добавить значение по заданному ключу в словарь. Если такой ключ уже есть, значение заменяется на новое.\n2 - Получить значение по заданному ключу из словаря. Если такого ключа нет, возвращается NULL.\n3 - Проверить наличие заданного ключа в словаре.\n4 - Удалить заданный ключ и связанное с ним значение из словаря. Если такого ключа нет, функция ничего не делает.\n");
	int command = scanOne();
	Node* tree = NULL;
	while (command != 0) {
		if (command == 1) {
			printf("Введите ключ\n");
			int key = scanOne();
			printf("Введите размер строки. Он не должен превышать 199 символов\n");
			int size = scanOne() + 1;
			char* string = calloc(size, sizeof(char));
			char buffer[200] = { '\0' };
			if (string == NULL) {
				return false;
			}
			while (strlen(buffer) != size - 1) {
				strcpy(buffer, "");
				printf("Введите строку!\n");
				int checkScanf = scanf("%s", buffer);
				while (checkScanf != 1) {
					while (getchar() != '\n') {
					}

					printf("Ошибка...\n");
					checkScanf = scanf("%s", buffer);
				}
			}
			strcpy(string, buffer);
			Node* check = addToBinaryTree(tree, key, string);
			if (check == NULL) {
				clearBinaryTree(tree);
				return false;
			}
			tree = check;
			printf("Введите следующую команду!\n");
		} else if (command == 2) {
			printf("Введите ключ\n");
			int key = scanOne();
			char* string = returnValueByKey(tree, key);
			if (string != NULL) {
				printf("%s\n", string);
			}
			printf("Введите следующую команду!\n");
		} else if (command == 3) {
			printf("Введите ключ\n");
			int key = scanOne();
			if (isThereAKeyInTheTree(tree, key)) {
				printf("Да, такой ключ имеется!\n");
			} else {
				printf("Нет, такого ключа нет!\n");
			}
			printf("Введите следующую команду!\n");
		} else if (command == 4) {
			printf("Введите ключ\n");
			int key = scanOne();
			tree = deleteNodeInTreeByKey(tree, key);
			printf("Введите следующую команду!\n");
		} else {
			printf("Вы ввели несуществующую команду. Попробуйте ещё раз!\n");
		}
		command = scanOne();
	}
	clearBinaryTree(tree);
}

bool test(void) {
	Node* tree = NULL;
	char* buffer = calloc(4, sizeof(char));
	if (buffer == NULL) {
		return false;
	}
	for (int i = 0; i < 3; ++i) {
		if (i == 0) {
			buffer[i] = 'e';
		} else if (i == 1) {
			buffer[i] = 'n';
		} else if (i == 2) {
			buffer[i] = 'd';
		}
	}
	tree = addToBinaryTree(tree, 100, buffer);
	if (strcmp(returnValueByKey(tree, 100), buffer) != 0) {
		return false;
	}
	if (!isThereAKeyInTheTree(tree, 100)) {
		return false;
	}
	
	tree = deleteNodeInTreeByKey(tree, 100);

	if (isThereAKeyInTheTree(tree, 100)) {
		return false;
	}
	return true;
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (test()) {
		printf("Тесты прошли успешно\n");
	} else {
		printf("Ошибка...");
	}

	if (!talkWithUser()) {
		printf("Ошибка!\n");
		return -1;
	}
}

int scanOne() {
	int number = 0;
	int checkScanf = scanf("%d", &number);

	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}

		printf("Ошибка...\n");
		checkScanf = scanf("%d", &number);
	}

	return number;
}