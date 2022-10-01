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
	for (int i = 12; i >= 13 - size; --i) {
		binaryNumber[i] = (number & 1);
		number = number >> 1;
	}
}

void printArrayBinary(bool *binaryNumber, int size, int maxPow2) {
	for (int i = maxPow2 - size; i < maxPow2; ++i) {
		printf("%d", binaryNumber[i]);
	}
	printf("\n");
}

void sumToBinary(bool *binaryNumber1, bool *binaryNumber2, int size1, int size2) {
	bool binaryNumber3[14] = {false};

	bool pastSum = false;
	int i = 12;
	int size3 = 0;

	while (i >= 0) {
		if (binaryNumber1[i] && binaryNumber2[i] && !pastSum) {
			binaryNumber3[i + 1] = false;
		} else if (!binaryNumber1[i] && binaryNumber2[i] && pastSum) {
			binaryNumber3[i + 1] = false;
		} else if (binaryNumber1[i] && !binaryNumber2[i] && pastSum) {
			binaryNumber3[i + 1] = false;
		} else {
			binaryNumber3[i + 1] = binaryNumber1[i] + binaryNumber2[i] + pastSum;
		}
		if (binaryNumber3[i + 1]) {
			size3 = 14 - i - 1;
		}
		pastSum = false;
		if (binaryNumber1[i] && binaryNumber2[i]) {
			pastSum = true;
		}
		--i;
	}

	if (binaryNumber1[0] && binaryNumber2[0]) {
		binaryNumber3[0] = true;
		size3 = 14;
	}

	printArrayBinary(binaryNumber3, size3, 14);
}

void toBinary(int number1, int number2) {
	number1 = number1 < 0 ? 4096 - number1 : number1;
	number2 = number2 < 0 ? 4096 - number2 : number2;
	int size1 = sizeBinary(number1);
	int size2 = sizeBinary(number2);
	bool binaryNumber1[13] = {false};
	bool binaryNumber2[13] = {false};
	
	translateDecToBin(binaryNumber1, size1, number1);
	translateDecToBin(binaryNumber2, size2, number2);

	printArrayBinary(binaryNumber1, size1, 13);
	printArrayBinary(binaryNumber2, size2, 13);

	for (int i = 0; i < 13; ++i) {
		printf("%d", binaryNumber1[i]);
	}
	printf("\n");
	for (int i = 0; i < 13; ++i) {
		printf("%d", binaryNumber2[i]);
	}
	printf("\n");

	sumToBinary(binaryNumber1, binaryNumber2, size1, size2);
}

int main() {
	setlocale(LC_ALL, "RUS");
	printf("%s", "Введите два числа, которые затем будут преобразованы в двоичное представление.Числа должны быть меньше 4096 по модулю\n");
	int number1 = scanOne();
	while (abs(number1) >= 4096) {
		printf("%s\n", "Введенное число превышает ограничение! Введите заново");
		number1 = scanOne();
	}
	int number2 = scanOne();
	while (abs(number2) >= 4096) {
		printf("%s\n", "Введенное число превышает ограничение! Введите заново");
		number2 = scanOne();
	}

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