#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

int scanOne();
void print(int number);

int sizeBinary(int number) {
	int size = 0;
	while (number) {
		number = number >> 1;
		++size;
	}
	return size;
}

void translateDecToBin(bool *binaryNumber, int size, int number) {
	for (int i = size - 1; i >= 0; --i) {
		binaryNumber[i] = (number & 1);
		number = number >> 1;
	}
}

void printArrayBinary(bool *binaryNumber, int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d", binaryNumber[i]);
	}
	printf("\n");
}

void toBinary(int number1, int number2) {
	int size1 = sizeBinary(number1);
	int size2 = sizeBinary(number2);
	bool *binaryNumber1 = (bool*)calloc(size1, sizeof(bool));
	bool *binaryNumber2 = (bool*)calloc(size2, sizeof(bool));
	
	translateDecToBin(binaryNumber1, size1, number1);
	translateDecToBin(binaryNumber2, size2, number2);

	printArrayBinary(binaryNumber1, size1);
	printArrayBinary(binaryNumber2, size2);

	free(binaryNumber1);
	free(binaryNumber2);
}

int main() {
	setlocale(LC_ALL, "RUS");
	printf("%s", "Введите два числа, которые затем будут преобразованы в двоичное представление\n");
	int number1 = scanOne();
	int number2 = scanOne();
	toBinary(number1, number2);
}

void print(int number) {
	printf("%d\n", number);
}

int scanOne() {
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