#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int scanOne();

void insertSort(int* arrayOut, int size) {
	if (arrayOut != NULL) {
		for (int i = 1; i < size; ++i) {
			int j = i;
			while (j >= 1 && arrayOut[j] < arrayOut[j - 1]) {
				int copyElement = arrayOut[j];
				arrayOut[j] = arrayOut[j - 1];
				arrayOut[j - 1] = copyElement;
				--j;
			}
		}
	}
}

void qSort(int* arrayOut, int size) {
	if (size <= 10) {

		return;
	}
}

int main() {
	setlocale(LC_ALL, "RUS");

	printf("%s", "Введите размер массива \n");
	int size = scanOne();
	int* arrayOut = (int*)calloc(size, sizeof(int));
	if (arrayOut != NULL) {
		for (int i = 0; i < size; ++i) {
			arrayOut[i] = scanOne();
		}
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