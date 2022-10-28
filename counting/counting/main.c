#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <locale.h>

int scanOne();

int whichPosition(int size, int step) {
	List* list = createList();
	addPositions(list, size);
	return counting(list, size, step);
}

int main() {
	setlocale(LC_ALL, "RUS");
	printf("Введите колличество людей\n");
	int size = scanOne();
	if (size == 0) {
		return 0;
	}
	printf("Введите шаг считалочки\n");
	int step = scanOne();
	printf("%s %d", "Позиции идут от нуля, начинается подсчёт с нулевого номера, после нахождения необходимой позиции подсчёт начинается со следущего. Необходимая позиция: ", whichPosition(size, step));
}

int scanOne() {
	int number = 0;
	int checkScanf = scanf("%d", &number);

	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}

		printf("Ошибка...\n");
		checkScanf = scanf("%d", &number);
	}

	return number;
}