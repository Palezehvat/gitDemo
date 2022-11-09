#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

bool scanFile(char fileName[], char arrayForTest[]) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Mistake!");
		return false;
	}
	char data[100] = { '\0' };
	int pointerTest = 0;
	while (fscanf(file, "%s", data) == 1){
		size_t sizeData = strlen(data);
		if (sizeData >= 1) {
			if (fileName != NULL && strcmp(fileName, "test.txt") != 0) {
				printf("%c", data[0]);
			} else {
				if (arrayForTest[pointerTest] != data[0]) {
					return false;
				}
				++pointerTest;
			}
		}
		for (size_t i = 1; i < sizeData; ++i) {
			if (data[i] != data[i - 1]) {
				if (fileName != NULL && strcmp(fileName, "test.txt") != 0) {
					printf("%c", data[i]);
				} else {
					if (arrayForTest[pointerTest] != data[i]) {
						return false;
					}
					++pointerTest;
				}
			}
		}
	}
	fclose(file);
	return true;
}

bool test(){
	char fileName[9] = "test.txt";
	char arrayTest[4] = "abc";
	return scanFile(fileName, arrayTest);
}

int main(void) {
		setlocale(LC_ALL, "RUS");
		if (test()) {
			printf("Tests correct\n");
		}
		else {
			printf("Mistake...\n");
			return 0;
		}
		printf("Enter the file name and its extension, the size should not exceed 100 characters. You cannot enter a file named test.txt.\n");
		char fileName[100] = { '\0' };
		int checkScan = scanf("%s", &fileName);

		while (checkScan != 1 || fileName == NULL || strcmp(fileName, "test.txt") == 0) {
			while (getchar() != '\n') {
			}
			printf("Mistake...Try again\n");
			checkScan = scanf("%s", &fileName);
		}
		if (!scanFile(fileName, NULL)) {
			printf("Mistake...\n");
			return -1;
		}
	}