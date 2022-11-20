#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

int scanOne(void);

void bubbleSort(int arrayEvenNumbered[], int size) {
	if (arrayEvenNumbered == NULL) {
		return;
	}
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			if (arrayEvenNumbered[j] < arrayEvenNumbered[j - 1]) {
				int temp = arrayEvenNumbered[j - 1];
				arrayEvenNumbered[j - 1] = arrayEvenNumbered[j];
				arrayEvenNumbered[j] = temp;
			}
		}
	}
}

void sortEvenNumberedPositions(int* arrayOut, int size) {
	int* arrayEvenNumbered = (int*)calloc(size, sizeof(int));
	if (arrayEvenNumbered == NULL) {
		return;
	}
	int j = 0;
	for (int i = 0; i < size; ++i) {
		if (arrayOut[i] % 2 == 0) {
			arrayEvenNumbered[j] = arrayOut[i];
			++j;
		}
	}
	bubbleSort(arrayEvenNumbered, j);
	int k = 0;
	int i = 0;
	for (int i = 0; i < size; ++i) {
		if (arrayOut[i] % 2 == 0) {
			arrayOut[i] = arrayEvenNumbered[k];
			++k;
		}
	}
	free(arrayEvenNumbered);
}

bool test(void) {
	int arrayOut[5] = { 5, 4, 3, 2, 1 };
	int arrayNeed[5] = { 5, 2, 3, 4, 1 };
	sortEvenNumberedPositions(arrayOut, 5);
	for (int i = 0; i < 5; ++i) {
		if (arrayOut[i] != arrayNeed[i]) {
			return false;
		}
	}
	return true;
}

int main(void) {
	setlocale(LC_ALL, "RUS");
	if (test()) {
		printf("Tests correct\n");
	}
	else {
		printf("Mistake...\n");
		return -1;
	}
	printf("Enter the size of the array\n");
	int size = scanOne();
	int* arrayOut = (int*)calloc(size, sizeof(int));
	if (arrayOut == NULL) {
		return -1;
	}
	printf("Enter the elements\n");
	for (int i = 0; i < size; ++i) {
		arrayOut[i] = scanOne();
	}
	sortEvenNumberedPositions(arrayOut, size);
	for (int i = 0; i < size; ++i) {
		printf("%d ", arrayOut[i]);
	}
	free(arrayOut);
}

int scanOne(void) {
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