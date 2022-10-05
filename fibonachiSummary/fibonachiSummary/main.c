#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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
		//printf("%d %d %d\n", firstElement, secondElement, sumElements);
	}
	return firstElement + secondElement;
}

int main() {
	setlocale(LC_ALL, "RUS");
	printf("%d", fibonacciIterative());
}