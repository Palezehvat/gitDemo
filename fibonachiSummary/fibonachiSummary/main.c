#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

bool test() {
	return fibonacciIterative() == 1089154;
}

int fibonacciIterative() {
	int firstElement = 1;
	int secondElement = 1;
	int i = 0;
	int lastSecondElement = 0;

	int sumElements = 0;
	while (secondElement < 1000000 && firstElement < 1000000) {
		secondElement = firstElement + secondElement;
		firstElement = secondElement - firstElement;
		++i;
		if (secondElement % 2 == 0) {
			sumElements += secondElement;
		}
		if (firstElement % 2 == 0 && firstElement != lastSecondElement) {
			sumElements += firstElement;
		}
		lastSecondElement = secondElement;
	}
	return sumElements;
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (test()) {
		printf("Все тесты пройдены успешно!\n");
	} else {
		printf("Тесты не пройдены...\n");
		return -1;
	}
	printf("%d", fibonacciIterative());
}