#include "test.h"

bool test() {
	Error check = ok;
	workWithFile(&check, "test.txt");
	if (check != ok) {
		return false;
	}
	FILE* file = fopen("test.txt", "r");
	if (file == NULL) {
		return false;
	}
	int arrayChecker[] = { 43, 32, 23, 122 };
	int i = 0;
	int number = 0;
	while (fscanf(file, "%d", &number) == 1) {
		if (number != arrayChecker[i]) {
			fclose(file);
			return false;
		}
		++i;
	}
	workWithFile(&check, "test.txt");
	return true;
}