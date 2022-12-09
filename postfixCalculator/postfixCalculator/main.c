#include <stdio.h>
#include "stack.h"
#include <locale.h>
#include <string.h>
#include <stdbool.h>

int calculate(const char stringOfActions[], int* errorCode) {
	size_t sizeString = strlen(stringOfActions);
	size_t i = 0;
	ElementStack* buffer = NULL;
	while (i < sizeString) {
		if (stringOfActions[i] >= '0' && stringOfActions[i] <= '9') {
			int multiplier = 10;
			int number = 0;
			while (stringOfActions[i] >= '0' && stringOfActions[i] <= '9') {
				number += stringOfActions[i] - '0';
				number *= multiplier;
				++i;
			}
			number /= 10;
			--i;
			pushElements(&buffer, number);
		} else if (stringOfActions[i] != ' ') {
			int numberAfter = 0;

			int firstNumber = popElements(&buffer, errorCode);
			if (*errorCode == 1) {
				return 0;
			}
			int secondNumber = popElements(&buffer, errorCode);
			if (*errorCode == 1) {
				return 0;
			}
			
			switch (stringOfActions[i]) {
			case '*':
				numberAfter = firstNumber * secondNumber;
				break;
			case '+':
				numberAfter = firstNumber + secondNumber;
				break;
			case '-':
				numberAfter = secondNumber - firstNumber;
				break;
			case '/':
				numberAfter = secondNumber / firstNumber;
				break;
			}
			
			if (*errorCode == 1) {
				clear(&buffer);
				return 0;
			}

			pushElements(&buffer, numberAfter);
		}
		++i;
	}

	int result = popElements(&buffer, errorCode);
	if (*errorCode == 1) {
		return 0;
	}

	if (buffer != NULL) {
		printf("Вы скорей всего ошиблись в вводе\n");
		return 0;
	}

	return result;
}

bool firstTest(void) {
	const char *testString = "1 2 +";
	int errorCode = 0;
	return calculate(testString, &errorCode) == 3 && errorCode == 0;
}

bool secondTest(void) {
	const char *testString = "1 2 + 4 3 * *";
	int errorCode = 0;
	return calculate(testString, &errorCode) == 36 && errorCode == 0;
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (!firstTest() || !secondTest()) {
		printf("Что-то пошло не так...\n");
		return -1;
	} else {
		printf("Тесты успешно пройдены!\n");
	}
	char stringOfActions[101] = {'\0'};
	printf("Введите последовательность цифр и арифметических действий, строка не должна превышать 100 символов\n");
	gets_s(stringOfActions, 100);
	int errorCode = 0;
	int result = calculate(stringOfActions, &errorCode);
	if (errorCode == 1) {
		printf("Ошибка...\n");
	} else {
		printf("%s %d\n", "Результат:", result);
	}
}