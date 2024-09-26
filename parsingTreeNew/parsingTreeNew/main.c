#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

bool isDigit(char symbol) {
	return symbol >= '0' && symbol <= '9';
}

bool readFromFileToTree(char fileName[], Tree* tree) {
	int errorCode = 0;
	FILE* file = fopen(fileName, "rt");
	if (file == NULL) {
		printf("���� �� ������!");
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
			}
			else {
				ungetc(symbol, file);
				fscanf(file, "%c", &letter);
				int number = -letter - '0';
				fscanf(file, "%c", &letter);
				while (isDigit(letter)) {
					number *= 10;
					number += letter - '0';
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
		printf("����� ������ �������!\n");
	}
	else {
		printf("������...\n");
		return -1;
	}
	printf("������� ��� ����� � ��� �����������, ������ �� ������ ��������� 100 ��������\n");
	char fileName[100] = { '\0' };
	int checkScan = scanf("%s", &fileName);
	while (checkScan != 1) {
		while (getchar() != '\n') {
		}

		printf("������...");
		checkScan = scanf("%s", &fileName);
	}
	if (!connectingFunction(fileName)) {
		printf("������...\n");
		return -1;
	}
}