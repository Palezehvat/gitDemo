#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

int scanOne();

bool readFromFile(char fileName[], int numberOrName) {
	List* list = createList();
	List* listCopy = createList();
	
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Ошибка!");
		return false;
	}
	char letter = 0;
	char name[100] = { '\0' };
	char number[100] = { '\0' };
	char buffer[100] = { '\0' };
	int stringInfile = 0;
	int size = 0;
	while (fscanf(file, "%s", buffer) == 1) {
		size_t sizeBuffer = strlen(buffer);
		size_t i = 0;
		if (stringInfile == 0) {
			while (i < sizeBuffer) {
				name[i] = buffer[i];
				++i;
			}
		}
		if (stringInfile == 2) {
			while (i < sizeBuffer) {
				number[i] = buffer[i];
				++i;
			}
			addRecord(list, name, number);
			addRecord(listCopy, NULL, NULL);
			memset(name, 0, strlen(name));
			memset(number, 0, strlen(number));
			stringInfile = -1;
		}
		++stringInfile;
		++size;
	}
	size /= 3;
	fclose(file);
	mergeSort(0, size - 1, list, listCopy, numberOrName);

	//if (strcmp(fileName, "test.txt") == 0) {
	//		return isSortedByNumber(list);
	//}
}

bool test(void) {
	return readFromFile("test.txt", 1);
}

int main() {
	setlocale(LC_ALL, "RUS");
	char fileName[100] = { '\0' };
	printf("Введите имя файла, с его расширением(Нельзя вводить: test.txt)\n");
	int checkScan = scanf("%s", &fileName);

	while (strcmp(fileName, "test.txt") == 0 || checkScan != 1) {
		while (getchar() != '\n') {
		}
		printf("Ошибка\n");
		checkScan = scanf("%s", &fileName);
	}
	printf("Введите почему сортировать(0 - по имени, 1 - по номеру)\n");
	int sortByNameOrNumber = scanOne();
	readFromFile(fileName, sortByNameOrNumber);
}

int scanOne() {
	int number = 0;
	int checkScanf = scanf("%d", &number);

	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}

		printf("Ошибка...\n");
		checkScanf = scanf("%d", &number);
	}

	return number;
}