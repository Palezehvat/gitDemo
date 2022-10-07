#include <stdio.h>
#include <stdlib.h>
#include "qSort.h"
#include <locale.h>
#include <stdbool.h>

int theMostCommonElement(char nameFile[]) {
	FILE* file = fopen(nameFile, "r");
	if (file == NULL) {
		printf("Файл не найден!");
		return -1;
	}
	int size = 0;
	if (fscanf(file, "%d", &size) < 0) {
		printf("Ошибка ввода\n");
		return -1;
	}
	
	int i = 0;
	int* arrayOut = (int*)calloc(size, sizeof(int));
	while (fscanf(file, "%d", &arrayOut[i]) >= 0) {
		++i;
	}

	qSort(arrayOut, 0, size - 1);
	int maxElements = arrayOut[0];
	int counter = 1;
	int maxCount = 1;

	for (int i = 0; i < size; ++i) {
		if (arrayOut[i - 1] != arrayOut[i]) {
			if (counter > maxCount) {
				maxCount = counter;
				maxElements = arrayOut[i - 1];
			}
			counter = 0;
		}
		++counter;
	}

	free(arrayOut);
	fclose(file);
	return maxElements;
}

bool test() {
	char buffer[27] = {'t','e','s','t','F','o','r','M','o','d','u','l','e','s','A','n','d','F','i','l','e','s','.','t','x','t','\0'};
	printf("%s", buffer);
}

int main() {
	setlocale(LC_ALL, "RUS");
	printf("Введите название файла. Пример: test.txt\n");

	char nameFile[100] = {'\0'};
	int checkScanf = (scanf("%s", &nameFile));
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}
		printf("Проверьте правильность ввода...\n");
		checkScanf = ("%s", &nameFile);
	}
	printf("%s", "Далее вам будет выведен самый частый элемент, в отсартированном массиве(сортировка: qSort), считанным из файла\n");

	int number = theMostCommonElement(nameFile);
	printf("%d", number);
}