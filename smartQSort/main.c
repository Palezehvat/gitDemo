#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int scanOne();

void 

void Qsort(int* arrayOut, int size) {
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