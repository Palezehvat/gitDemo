#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include <string.h>
#include <locale.h>

bool converterToPostfixForm(char buffer[], char result[]) {
	
	return true;
}


int main() {
	setlocale(LC_ALL, "RUS");
	printf("Введите строку примера в итеративной форме\n");
	char buffer[100] = { '\0' };
	gets_s(buffer, 100);
	char result[100] = { '\0' };
	converterToPostfixForm(buffer, result);
	printf("%s", result);
}