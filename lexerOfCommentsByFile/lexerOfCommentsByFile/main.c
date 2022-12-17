#include "lexerOfComments.h"
#include <stdio.h>
#include <stdlib.h>
#include "test.h"


int main() {
	if (test()) {
		printf("Tests correct!\n");
	} else {
		printf("Error\n");
		return -1;
	}
	Error errorCheck = ok;
	printf("Input your file with extension. No more than 100 symbols\n");
	char nameFile[101] = { '\0' };
	int checkScanf = scanf_s("%s", nameFile, 100);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}
		printf("Try again\n");
		checkScanf = scanf_s("%s", nameFile, 100);
	}
	char* buffer = lexerOfComments("table.txt", nameFile, &errorCheck);
	if (errorCheck != ok) {
		printf("Error\n");
		return -1;
	}
	printf("%s", buffer);
}