#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

int scanOne();
void print(int number);

int binaryToDecimal(bool *binaryNumber)
{
	int multiplier = 1;
	int number = 0;
	for (int i = 11; i >= 0; --i) {
		number += multiplier * binaryNumber[i];
		multiplier = multiplier << 1;
	}
	
	return binaryNumber[0] ? number - 4096 : number;
}
int sizeBinary(int number) {
	int size = 0;
	while (number) {
		number = number >> 1;
		++size;
	}
	return size;
}

void translateDecimalToBinary(bool *binaryNumber, int size, int number) {
	for (int i = 11; i >= 12 - size; --i) {
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

void sumToBinary(bool *binaryNumber1, bool *binaryNumber2, bool binaryNumber3[], int size1, int size2) {
	bool pastSum = false;
	int i = 11;
	int size3 = 0;

	while (i >= 0) {
		if (binaryNumber1[i] && binaryNumber2[i] && !pastSum || !binaryNumber1[i] && binaryNumber2[i] && pastSum || binaryNumber1[i] && !binaryNumber2[i] && pastSum) {
			binaryNumber3[i] = false;
			pastSum = true;
		} else if (binaryNumber1[i] && binaryNumber2[i] && pastSum) {
			binaryNumber3[i] = binaryNumber1[i] + binaryNumber2[i] + pastSum;
			pastSum = true;
		} else {
			binaryNumber3[i] = binaryNumber1[i] + binaryNumber2[i] + pastSum;
			pastSum = false;
		}
		if (binaryNumber3[i]) {
			size3 = 12 - i;
		}
		--i;
	}

	if (binaryNumber1[0] && binaryNumber2[0]) {
		binaryNumber3[0] = true;
		size3 = 12;
	}
}

int toChangeNegativeNumbers(int number) {
	return number < 0 ? 4096 + number : number;
}

bool testStandart(void) {
	int size1 = sizeBinary(12);
	int size2 = sizeBinary(13);
	bool* binaryNumber1 = (bool*)calloc(12, sizeof(int));
	bool* binaryNumber2 = (bool*)calloc(12, sizeof(int));
	translateDecimalToBinary(binaryNumber1, size1, 12);
	translateDecimalToBinary(binaryNumber2, size2, 13);
	bool* binaryNumber3 = (bool*)calloc(12, sizeof(int));
	sumToBinary(binaryNumber1, binaryNumber2, binaryNumber3, size1, size2);
	free(binaryNumber1);
	free(binaryNumber2);
	int result = binaryToDecimal(binaryNumber3);
	free(binaryNumber3);
	return result == 25;
}

bool testNotStandart() {
	int number1 = toChangeNegativeNumbers(1001);
	int number2 = toChangeNegativeNumbers(-1002);
	int size1 = sizeBinary(number1);
	int size2 = sizeBinary(number2);
	bool* binaryNumber1 = (bool*)calloc(12, sizeof(int));
	bool* binaryNumber2 = (bool*)calloc(12, sizeof(int));
	translateDecimalToBinary(binaryNumber1, size1, number1);
	translateDecimalToBinary(binaryNumber2, size2, number2);
	bool* binaryNumber3 = (bool*)calloc(12, sizeof(int));
	sumToBinary(binaryNumber1, binaryNumber2, binaryNumber3, size1, size2);
	free(binaryNumber1);
	free(binaryNumber2);
	int result = binaryToDecimal(binaryNumber3);
	free(binaryNumber3);
	return result == -1;
}

int main() {
	setlocale(LC_ALL, "RUS");
	
	if (!testStandart() || !testNotStandart()) {
		printf("%s", "Тесты не пройдены\n");
		return 0;
	} else {
		printf("%s", "Тесты успешно пройдены\n");
	}
	
	printf("%s", "Введите два числа, которые затем будут преобразованы в двоичное представление.Числа и их сумма должны быть меньше 2048 по модулю\n");
	int number1 = scanOne();
	while (abs(number1) >= 2048) {
		printf("%s\n", "Введенное число превышает ограничение! Введите заново");
		number1 = scanOne();
	}
	int number2 = scanOne();
	while (abs(number2) >= 2048 || abs(number1 + number2) >= 2048) {
		printf("%s\n", "Введенное число превышает ограничение! Введите заново");
		number1 = scanOne();
		number2 = scanOne();
	}
	number1 = toChangeNegativeNumbers(number1);
	number2 = toChangeNegativeNumbers(number2);
	int size1 = sizeBinary(number1);
	int size2 = sizeBinary(number2);
	bool *binaryNumber1 = (bool*)calloc(12, sizeof(int));
	bool *binaryNumber2 = (bool*)calloc(12, sizeof(int));
	translateDecimalToBinary(binaryNumber1, size1, number1);
	translateDecimalToBinary(binaryNumber2, size2, number2);
	printArrayBinary(binaryNumber1, size1, 12);
	printArrayBinary(binaryNumber2, size2, 12);
	int size3 = 12;
	bool *binaryNumber3 = (bool*)calloc(12, sizeof(int));
	sumToBinary(binaryNumber1, binaryNumber2,binaryNumber3, size1, size2);
	printArrayBinary(binaryNumber3, size3, 12);
	printf("%d", binaryToDecimal(binaryNumber3));
	free(binaryNumber1);
	free(binaryNumber2);
	free(binaryNumber3);
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