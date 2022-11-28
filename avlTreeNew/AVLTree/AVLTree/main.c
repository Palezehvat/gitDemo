#include "avlTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

int scanOne();

bool talkWithUser(void) {
	printf("У вас есть следующие команды:\n0 - Выйти из интерактивного меню\n1 - Добавить значение по заданному ключу в словарь. Если такой ключ уже есть, значение заменяется на новое.\n2 - Получить значение по заданному ключу из словаря.Если такого ключа нет, возвращается NULL.\n3 - Проверить наличие заданного ключа.\n4- Удалить заданный ключ и связанное с ним значение из словаря.Если такого ключа нет, функция ничего не делает.\n");
	int command = scanOne();

	while (command > 4 || command < 0) {
		printf("Вы ввели несуществующую команду. Попробуйте ещё раз!\n");
		command = scanOne();
	}

	Tree* tree = createTree();
	char* stringCopy = NULL;

	while (command != 0) {
		printf("Введите ключ\n");
		int key = scanOne();

		switch (command) {
		case 1:
			printf("Введите размер строки. Он не должен превышать 100 символов, а затем введите строку\n");
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
				return false;
			}
			for (size_t i = 0; i < sizeBuffer; ++i) {
				string[i] = buffer[i];
			}
			addToTree(tree, key, string);
			break;
		case 2:
			stringCopy = NULL;
			stringCopy = returnValueByKey(tree, key);
			if (string != NULL) {
				printf("%s\n", string);
			}
			break;
		case 3:
			if (isKeyInTree(tree, key)) {
				printf("Да, такой ключ имеется!\n");
			}
			else {
				printf("Нет, такого ключа нет!\n");
			}
			break;
		case 4:
			deleteNodeInTreeByKey(tree, key);
			break;
		}
		printf("Введите следующую команду!\n");
		command = scanOne();

		while (command > 4 || command < 0) {
			printf("Вы ввели несуществующую команду. Попробуйте ещё раз!\n");
			command = scanOne();
		}
	}

	clearTree(tree);
}

bool test() {
	FILE* file = fopen("test.txt", "r");
	if (file == NULL) {
		return false;
	}
	int key = 0;
	char string[2] = { 'a', '\0' };
	Tree* tree = createTree();
	while (fscanf(file, "%d", &key) == 1) {
		addToTree(tree, key, string);
	}

	deleteNodeInTreeByKey(tree, 100);
	fclose(file);
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (test()) {
		printf("Тесты прошли успешно!\n");
	}
	else {
		printf("Ошибка...\n");
		return -1;
	}
	if (!talkWithUser()) {
		printf("Ошибка...\n");
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