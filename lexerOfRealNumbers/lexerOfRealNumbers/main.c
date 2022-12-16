#include "lexer.h"
#include "test.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
	if (test()) {
		printf("Tests correct!\n");
	} else {
		printf("ERROR...\n");
		return -1;
	}
	printf("Input string no more than 100symbols\n");
	char string[101] = { '\0' };
	scanf_s("%s", string, 100);
	if (isTheSequenceANumber(string)) {
		printf("It is number\n");
	} else {
		printf("It is not number\n");
	}
}