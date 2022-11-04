#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

bool readFromFileToTree(char fileName[], Tree* tree) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Файл не найден!");
		return false;
	}
}

bool connectingFunction(char fileName[]) {
	Tree* tree = createTree();
}

bool test() {
	return true;
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

}