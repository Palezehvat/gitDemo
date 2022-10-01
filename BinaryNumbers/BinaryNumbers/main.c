#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

void toBinary(int number1, int number2) {
	int size1 = sizeBinary(number1);
	int size2 = sizeBinary(number2);
	int *binaryNumber1 = (int*)calloc(size1, sizeof(int));
	int *binaryNumber2 = (int*)calloc(size2, sizeof(int));


	free(binaryNumber1);
	free(binaryNumber2);
}

int main() {
	setlocale(LC_ALL, "RUS");
	printf("%s", "Введите два числа, которые затем будут преобразованы в двоичное представление\n");
	int number1 = scanOne();
	int number2 = scanOne();
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