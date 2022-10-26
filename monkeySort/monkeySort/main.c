#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int scanOne();

bool isSorted(int* arrayOut, int size) {
	if (arrayOut == NULL) {
		return false;
	}

	for (int i = 1; i < size; ++i) {
		if (arrayOut[i] < arrayOut[i - 1]) {
			return false;
		}
	}
	return true;
}

bool monkeySort(int* arrayOut, int size) {
	srand((unsigned int)time(NULL));
	if (arrayOut == NULL) {
		return false;
	}
	while (!isSorted(arrayOut, size)) {
		int firstIndex = rand() % size;
		int secondIndex = rand() % size;
		int number = 0;
		number = arrayOut[firstIndex];
		arrayOut[firstIndex] = arrayOut[secondIndex];
		arrayOut[secondIndex] = number;
	}
	return true;
}

bool test(void) {
	int arrayOut[3] = {3, 2, 1};
	if (!monkeySort(arrayOut, 3)) {
		return false;
	}
	return isSorted(arrayOut, 3);
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (test()) {
		printf("Тесты прошли успешно!\n");
	} else {
		printf("Ошибка...\n");
		return 0;
	}
	printf("Введите размер массива\n");
	int size = scanOne();
	if (size == 0) {
		return 0;
	}
	int* arrayOut = (int*)calloc(size, sizeof(int));
	if (arrayOut == NULL) {
		printf("Ошибка выделения памяти\n");
		return 0;
	}
	printf("Введите элементы массива\n");
	for (int i = 0; i < size; ++i) {
		arrayOut[i] = scanOne();
	}
	if (!monkeySort(arrayOut, size)) {
		printf("Ошибка...\n");
		return 0;
	}
	for (int i = 0; i < size; ++i) {
		printf("%d ", arrayOut[i]);
	}

	free(arrayOut);
}

int scanOne() {
	int number = 0;
	int checkScanf = scanf("%d", &number);

	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}

		printf("%s", "Ошибка... Проверьте правильность ввода \n");
		checkScanf = scanf("%d", &number);
	}

	return number;
}