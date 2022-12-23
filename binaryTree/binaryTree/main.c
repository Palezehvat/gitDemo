#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int scanOne();

bool talkWithUser(void) {
	printf("Введите одну из следующих команд\n0 - Выход из интерактивного меню.\n1 - Добавить значение по заданному ключу в словарь. Если такой ключ уже есть, значение заменяется на новое.\n2 - Получить значение по заданному ключу из словаря. Если такого ключа нет, возвращается NULL.\n3 - Проверить наличие заданного ключа в словаре.\n4 - Удалить заданный ключ и связанное с ним значение из словаря. Если такого ключа нет, функция ничего не делает.\n");
	int command = scanOne();
	while (command > 4 || command < 0) {
		printf("Вы ввели несуществующую команду. Попробуйте ещё раз!\n");
		command = scanOne();
	}
	Node* tree = NULL;
	char* stringCopy = NULL;

	while (command != 0) {

		printf("Введите ключ\n");
		int key = scanOne();
		
		switch (command) {
			case 1:
				printf("Введите размер строки. Он не должен превышать 100 символов\n");
				int size = scanOne();
				while (size < 0 || size > 100) {
					while (getchar() != '\n') {
					}
					printf("Ошибка...\n");
					size = scanOne();
				}
				char buffer[101] = { '\0' };
				int checkScanf = scanf("%s", buffer);

				while (checkScanf != 1) {
					while (getchar() != '\n') {
					}
					printf("Ошибка...\n");
					checkScanf = scanf("%s", buffer);
				}
				size_t sizeBuffer = strlen(buffer);
				char* string = calloc(sizeBuffer + 1, sizeof(char));
				if (string == NULL) {
					clearBinaryTree(tree);
					return false;
				}
				for (size_t i = 0; i < sizeBuffer; ++i) {
					string[i] = buffer[i];
				}
				Node* check = addToBinaryTree(tree, key, string);
				if (check == NULL) {
					clearBinaryTree(tree);
					return false;
				}
				tree = check;
				printf("Введите следующую команду!\n");
				break;
			case 2://
				stringCopy = returnValueByKey(tree, key);
				if (string != NULL) {
					printf("%s\n", string);
				}
				printf("Введите следующую команду!\n");
				break;
			case 3:
				if (isKeyInTree(tree, key)) {
					printf("Да, такой ключ имеется!\n");
				} else {
					printf("Нет, такого ключа нет!\n");
				}
				printf("Введите следующую команду!\n");
				break;
			case 4:
				tree = deleteNodeInTreeByKey(tree, key);
				printf("Введите следующую команду!\n");
				break;
		}

		command = scanOne();

		while (command > 4 || command < 0) {
			printf("Вы ввели несуществующую команду. Попробуйте ещё раз!\n");
			command = scanOne();
		}
	}

	clearBinaryTree(tree);
	return true;
}

bool test(void) {
	char* buffer = calloc(4, sizeof(char));
	if (buffer == NULL) {
		return false;
	}
	buffer = "end";
	Node* tree = addToBinaryTree(NULL, 100, buffer);
	if (strcmp(returnValueByKey(tree, 100), buffer) != 0) {
		clearBinaryTree(tree);
		return false;
	}
	if (!isKeyInTree(tree, 100)) {
		clearBinaryTree(tree);
		return false;
	}
	
	tree = deleteNodeInTreeByKey(tree, 100);

	if (isKeyInTree(tree, 100)) {
		clearBinaryTree(tree);
		return false;
	}
	clearBinaryTree(tree);
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