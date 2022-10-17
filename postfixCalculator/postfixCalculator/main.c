#include <stdio.h>
#include "stack.h"
#include <locale.h>
#include <string.h>
#include <stdbool.h>

int scanOne();

void elementsForStack(char stringOfActions[]) {
	size_t sizeString = strlen(stringOfActions);
	size_t i = 0;
	while(i < sizeString) {
		int number = 0;
		int multiplier = 1;
		while (stringOfActions[i] >= '0' && stringOfActions[i] <= '9') {
			number *= multiplier;
			number += ((int)stringOfActions[i] - 48);
			multiplier = 10;
			++i;
		}
		printf("%d", number);
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	char stringOfActions[100] = {'\0'};
	printf("Введите последовательность цифр и арифметических действий, строка не должна превышать 100 символов\n");
	int checkScanf = scanf("%s", &stringOfActions);
	while (checkScanf != 1)
	{
		while (getchar() != '\n') {
		}
		printf("%s", "Ошибка... Возможно вы неправильно что-то ввели или превысили размеры строк. \n");
		int checkScanf = scanf("%s", &stringOfActions);
	}
	elementsForStack(stringOfActions);

}

int scanOne() {
	int number = 0;
	int checkScanf = scanf("%d", &number);
	printf("2 %c", checkScanf);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}

		printf("%s", "Ошибка... Проверьте правильность ввода \n");
		checkScanf = scanf("%d", &number);
	}

	return number;
}