#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int scanOne();
void qSort(int* arrayOut, int startArray, int endArray);
int partition(int* arrayOut, int startArray, int endArray);
void insertSort(int* arrayOut, int startArray, int endArray);

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
	printf("%s\n", "Введите размер массива");
	int size = scanOne();
	printf("%s\n", "Введите элементы массива");
	int* arrayOut = (int*)calloc(size, sizeof(int));
	if (arrayOut == NULL) {
		return 0;
	}
	for (int i = 0; i < size; ++i) {
		arrayOut[i] = scanOne();
	}
	qSort(arrayOut, 0, size - 1);
	for (int i = 0; i < size; ++i) {
		printf("%d ", arrayOut[i]);
	}
}

int scanOne() {
	int number = 0;
	int checkScanf = scanf_s("%d", &number);

	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}

		printf("%s", "Ошибка... Проверьте правильность ввода \n");
		checkScanf = scanf_s("%d", &number);
	}

	return number;
}