#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

bool isDigit(char symbol) {
	return symbol == '0' || symbol == '1' || symbol == '2' || symbol == '3' || symbol == '4' || symbol == '5' || symbol == '6' || symbol == '7' || symbol == '8' || symbol == '9';
}

bool readFromFileToTree(char fileName[], Tree* tree) {
	int errorCode = 0;
	FILE* file = fopen(fileName, "rt");
	if (file == NULL) {
		printf("Файл не найден!");
		return false;
	}
	char letter = 0;

	while (!feof(file)) {
		fscanf(file, "%c", &letter);
		if (letter == '+' || letter == '*' || letter == '/') {
			addToTreeSymbol(tree, letter, &errorCode);
			if (errorCode != 0) {
				return false;
			}
		}
		if (letter == '-') {
			int symbol = getc(file);
			if (symbol == ' ') {
				addToTreeSymbol(tree, letter, &errorCode);
				if (errorCode != 0) {
					return false;
				}
				ungetc(symbol, file);
			} else {
				ungetc(symbol, file);
				fscanf(file, "%c", &letter);
				int number = -1 * (int)letter - 48;
				fscanf(file, "%c", &letter);
				while (isDigit(letter)) {
					number *= 10;
					number += (int)letter - 48;
					fscanf(file, "%c", &letter);
				}
				addToTreeNumber(tree, number, &errorCode);
				if (errorCode != 0) {
					return false;
				}
			}
		}
		if (isDigit(letter)) {
			int number = (int)letter - 48;
			fscanf(file, "%c", &letter);
			while (isDigit(letter)) {
				number *= 10;
				number += (int)letter - 48;
				fscanf(file, "%c", &letter);
			}
			addToTreeNumber(tree, number, &errorCode);
			if (errorCode != 0) {
				return false;
			}
		}
	}
	return true;
}

bool connectingFunction(char fileName[]) {
	Tree* tree = createTree();
	if (!readFromFileToTree(fileName, tree)) {
		return false;
	}
	printTree(tree);
	int errorCode = 0;
	int number = postorderCount(tree, &errorCode);
	if (errorCode != 0) {
		return -1;
	}
	printf("%d\n", number);
	clearTree(tree);
	return true;
}

bool test() {
	Tree* tree = createTree();
	if (!readFromFileToTree("test.txt", tree)) {
		return false;
	}
	int errorCode = 0;
	int number = postorderCount(tree, &errorCode);
	if (errorCode != 0) {
		return -1;
	}
	clearTree(tree);
	return number == -4;
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (test()) {
		printf("Тесты прошли успешно!\n");
	} else {
		printf("Ошибка...\n");
		return -1;
	}
	printf("Введите имя файла с его расширением, строка не должна превышать 100 символов\n");
	char fileName[100] = { '\0' };
	int checkScan = scanf("%s", &fileName);
	while (checkScan != 1) {
		while (getchar() != '\n') {
		}

		printf("Ошибка...");
		checkScan = scanf("%s", &fileName);
	}
	if (!connectingFunction(fileName)) {
		printf("Ошибка...\n");
		return -1;
	}
}