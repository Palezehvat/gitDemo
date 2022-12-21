#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool test() {
	char nameFile[] = "test.txt";
	char trueAnswer[] = "A.%@A9.A";
	Error errorCheck = ok;
	char* result = workWithFileAndReturnString(nameFile, &errorCheck);
	if (errorCheck != ok) {
		return false;
	}
	return strcmp(trueAnswer, result) == 0;
}

int main() {
	if (test()) {
		printf("Test correct\n");
	} else {
		printf("Error\n");
		return -1;
	}
	printf("Write the name of the file with its extension. No more than 99 symbols\n");
	char nameFile[100] = { '\0' };
	int checkScanf = scanf("%s", nameFile);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}

		checkScanf = scanf("%s", nameFile);
	}
	Error errorCheck = ok;
	char* result = workWithFileAndReturnString(nameFile, &errorCheck);
	if (errorCheck != ok) {
		printf("Error\n");
		return -1;
	}
	printf("%s\n", result);
}