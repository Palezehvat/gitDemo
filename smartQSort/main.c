#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

int scanOne();
void qSort(int* arrayOut, int startArray, int endArray);
int partition(int* arrayOut, int startArray, int endArray);
void insertSort(int* arrayOut, int startArray, int endArray);

bool testCorrectValue() {
	int arrayOut[15] = { 28, 96, 34, 70, 62, 59, 100, 9, 59, 91, 90, 64, 16, 48, 70 };
	qSort(arrayOut, 0, 14);
	for (int i = 1; i < 15; ++i) {
		if (arrayOut[i] < arrayOut[i - 1]) {
			return false;
		}
	}
	return true;
}

bool testAnotherValue() {
	int arrayOut[3] = { 1, 1, 1 };
	qSort(arrayOut, 0, 2);
	for (int i = 1; i < 3; ++i) {
		if (arrayOut[i] < arrayOut[i - 1]) {
			return false;
		}
	}
	return true;
}

void insertSort(int* arrayOut, int startArray, int endArray) {
	if (arrayOut != NULL) {
		for (int i = startArray + 1; i <= endArray; ++i) {
			int j = i;
			while (j >= startArray + 1 && arrayOut[j] < arrayOut[j - 1]) {
				int copyElement = arrayOut[j];
				arrayOut[j] = arrayOut[j - 1];
				arrayOut[j - 1] = copyElement;
				--j;
			}
		}
	}
}

int partition(int* arrayOut, int startArray, int endArray) {
	int pivot = arrayOut[endArray];
	int i = startArray;

	if (arrayOut != NULL) {
		for (int j = startArray; j < endArray; ++j) {
			if (arrayOut[j] <= pivot) {
				int copyElement = arrayOut[j];
				arrayOut[j] = arrayOut[i];
				arrayOut[i] = copyElement;
				++i;
			}
		}

		int copyElement = arrayOut[i];
		arrayOut[i] = arrayOut[endArray];
		arrayOut[endArray] = copyElement;
	}
	return i;
}

void qSort(int* arrayOut, int startArray, int endArray) {
	if (endArray - startArray + 1 <= 10) {
		insertSort(arrayOut, startArray, endArray);
		return;
	}
	if (startArray < endArray) {
		int positionElement = partition(arrayOut, startArray, endArray);
		qSort(arrayOut, startArray, positionElement - 1);
		qSort(arrayOut, positionElement + 1, endArray);
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (!testAnotherValue() || !testCorrectValue()) {
		printf("%s", "Тесты не пройдены... \n");
	} else {
		printf("%s", "Тесты пройдены \n");
	}
	printf("%s", "Введите размер массива \n");
	int size = scanOne();
	int* arrayOut = (int*)calloc(size, sizeof(int));
	if (arrayOut != NULL) {
		for (int i = 0; i < size; ++i) {
			arrayOut[i] = scanOne();
		}
	}
	qSort(arrayOut, 0, size - 1);
	if (arrayOut != NULL) {
		for (int i = 0; i < size; ++i) {
			printf("%d ", arrayOut[i]);
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