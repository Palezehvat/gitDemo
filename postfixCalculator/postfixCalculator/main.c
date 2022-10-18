#include <stdio.h>
#include "stack.h"
#include <locale.h>
#include <string.h>
#include <stdbool.h>

int plus(ElementStack** buffer, int* errorCode) {
	if (*buffer == NULL) {
		*errorCode = 0;
		return 0;
	}
	int firstNumber = popElements(buffer, errorCode);
	if (*errorCode == 1) {
		return 0;
	}
	int secondNumber = popElements(buffer, errorCode);
	if (*errorCode == 1) {
		return 0;
	}
	return firstNumber + secondNumber;
}

int minus(ElementStack** buffer, int* errorCode) {
	if (*buffer == NULL) {
		*errorCode = 0;
		return 0;
	}
	int firstNumber = popElements(buffer, errorCode);
	if (*errorCode == 1) {
		return 0;
	}
	int secondNumber = popElements(buffer, errorCode);
	if (*errorCode == 1) {
		return 0;
	}
	return secondNumber - firstNumber;
}

int multiply(ElementStack** buffer, int* errorCode) {
	if (*buffer == NULL) {
		*errorCode = 0;
		return 0;
	}
	int firstNumber = popElements(buffer, errorCode);
	if (*errorCode == 1) {
		return 0;
	}
	int secondNumber = popElements(buffer, errorCode);
	if (*errorCode == 1) {
		return 0;
	}
	return firstNumber * secondNumber;
}

int divide(ElementStack** buffer, int* errorCode) {
	if (*buffer == NULL) {
		*errorCode = 1;
		return 0;
	}
	int firstNumber = popElements(buffer, errorCode);
	if (*errorCode == 1) {
		return 0;
	}
	int secondNumber = popElements(buffer, errorCode);
	if (*errorCode == 1) {
		return 0;
	}

	return  secondNumber / firstNumber;
}

int elementsForStack(char stringOfActions[], int* errorCode) {
	size_t sizeString = strlen(stringOfActions);
	size_t i = 0;
	ElementStack* buffer = NULL;
	while(i < sizeString) {
		int number = 0;
		int multiplier = 1;
		if (stringOfActions[i] >= '0' && stringOfActions[i] <= '9') {
			while (stringOfActions[i] >= '0' && stringOfActions[i] <= '9') {
				number *= multiplier;
				number += ((int)stringOfActions[i] - 48);
				multiplier = 10;
				++i;
			}
			--i;
			pushElements(&buffer, number);
		} else {
			if (stringOfActions[i] == '*') {
				int numberAfter = multiply(&buffer, errorCode);
				if (*errorCode == 1) {
					return 0;
				}
				pushElements(&buffer, numberAfter);
			}
			else if (stringOfActions[i] == '+') {
				int numberAfter = plus(&buffer, errorCode);
				if (*errorCode == 1) {
					return 0;
				}
				pushElements(&buffer, numberAfter);
			}
			else if (stringOfActions[i] == '-') {
				int numberAfter = minus(&buffer, errorCode);
				if (*errorCode == 1) {
					return 0;
				}
				pushElements(&buffer, numberAfter);
			}
			else if (stringOfActions[i] == '/') {
				int numberAfter = divide(&buffer, errorCode);
				if (*errorCode == 1) {
					return 0;
				}
				pushElements(&buffer, numberAfter);
			}
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
	char testString[6] = { '1',' ', '2', ' ', '+', '\0' };
	int errorCode = 0;
	return elementsForStack(testString, &errorCode) == 3 && errorCode == 0 ? true : false;
}

bool seconfTest(void) {
	char testString[14] = { '1',' ', '2', ' ', '+', ' ', '4', ' ', '3', ' ', '*', ' ', '*', '\0' };
	int errorCode = 0;
	return elementsForStack(testString, &errorCode) == 36 && errorCode == 0 ? true : false;
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (!firstTest() || !seconfTest()) {
		printf("Что-то пошло не так...\n");
		return 0;
	} else {
		printf("Тесты успешно пройдены!\n");
	}
	char stringOfActions[101] = {'\0'};
	printf("Введите последовательность цифр и арифметических действий, строка не должна превышать 100 символов\n");
	gets_s(stringOfActions, 100);
	int errorCode = 0;
	int result = elementsForStack(stringOfActions, &errorCode);
	if (errorCode == 1) {
		printf("Ошибка...\n");
	} else {
		printf("%s %d\n", "Результат:", result);
	}
}