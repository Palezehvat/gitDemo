#include <stdio.h>
#include <stdlib.h>
#include "qSort.h"
#include <locale.h>

int theMostCommonElement() {
	FILE* file = fopen("Data.txt", "a");
	if (file == NULL) {
		printf("%s", "Файл не найден!");
		return -1;
	}
	int size = fscanf(file, "%d", &size) != 1;
	
	printf("%d", size);
	int i = 0;
	int* arrayOut = (int*)calloc(size, sizeof(int));
	while (fscanf(file, "%d", &arrayOut[i]) == 1) {
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

int main() {
	setlocale(LC_ALL, "RUS");
	printf("%s", "Далее вам будет выведен самый частый элемент, в отсартированном массиве(сортировка: qSort), считанным из файла\n");

	int number = theMostCommonElement();
	printf("%d", number);
}