#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

bool scanFile(int arrayOut[], char fileName[]) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Файл не найден!");
		return false;
	}
	char data[100] = { '\0' };
	while (fscanf(file, "%s", data) == 1) {
		size_t sizeData = strlen(data);
		for (int i = 0; i < sizeData; ++i) {
			++arrayOut[(int)data[i]];
		}
	}
	fclose(file);
	return true;
}

bool test() {
	char fileName[9] = "test.txt";
	int arrayOut[128] = { 0 };
	if (scanFile(arrayOut, fileName) == -1) {
		printf("Ошибка...\n");
		return false;
	}
	if (arrayOut[97] != 3 && arrayOut[98] != 2 && arrayOut[99] != 1) {
		return false;
	}
	return true;
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (test()) {
		printf("Тесты прошли успешно\n");
	} else {
		printf("Ошибка...\n");
		return 0;
	}
	int arrayOut[128] = { 0 };
	printf("Введите название файла(с расширением), он будет считан, и будет выведено колличество различных символов из строки\n");
	char fileName[100] = { '\0' };
	int checkScan = scanf("%s", &fileName);

	while (checkScan != 1) {
		while (getchar() != '\n') {
		}
		printf("Ошибка...\n");
		checkScan = scanf("%s", &fileName);
	}
	if (!scanFile(arrayOut, fileName)) {
		printf("Ошибка...\n");
		return 0;
	}
	for (int i = 0; i < 128; ++i) {
		if (arrayOut[i] != 0) {
			printf("%c: %d\n", (char)i, arrayOut[i]);
		}
	}
}