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

void printArrayBinary(bool *binaryNumber, int size) {
	for (int i = 13 - size; i < 13; ++i) {
		printf("%d", binaryNumber[i]);
	}
	printf("\n");
}
/*
void sumToBinary(int *binaryNumber1, int *binaryNumber2, int size1, int size2) {
	int size3 = size1 + size2;
	bool *binaryNumber3 = (bool*)calloc(size3, sizeof(int));

	int pastSum = -1;
	int i = max(size1, size2) - 1;
	while (i != 0) {
		if (i > size1) {
			
		} else if (i > size2) {

		} else {

		}
	}
}
*/
void toBinary(int number1, int number2) {
	number1 = number1 < 0 ? 4096 - number1 : number1;
	number2 = number2 < 0 ? 4096 - number2 : number2;
	int size1 = sizeBinary(number1);
	int size2 = sizeBinary(number2);
	bool binaryNumber1[13] = {false};
	bool binaryNumber2[13] = {false};
	
	translateDecToBin(binaryNumber1, size1, number1);
	translateDecToBin(binaryNumber2, size2, number2);

	printArrayBinary(binaryNumber1, size1);
	printArrayBinary(binaryNumber2, size2);
}

int main() {
	setlocale(LC_ALL, "RUS");
	printf("%s", "������� ��� �����, ������� ����� ����� ������������� � �������� �������������.����� ������ ���� ������ 4096 �� ������\n");
	int number1 = scanOne();
	while (abs(number1) >= 4096) {
		printf("%s\n", "��������� ����� ��������� �����������! ������� ������");
		number1 = scanOne();
	}
	int number2 = scanOne();
	while (abs(number2) >= 4096) {
		printf("%s\n", "��������� ����� ��������� �����������! ������� ������");
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

		printf("%s", "������... ��������� ������������ ����� \n");
		checkScanf = scanf("%d", &number);
	}

	return number;
}