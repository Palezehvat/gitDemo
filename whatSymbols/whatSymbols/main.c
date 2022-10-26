#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

void scanFile(int arrayOut[], char fileName[]) {
	FILE* file = fopen("test.txt", "r");
	if (file == NULL) {
		printf("‘айл не найден!");
		return -1;
	}
	char data[100] = { '\0' };
	while (fscanf(file, "%s", data) == 1) {
		size_t sizeData = strlen(data);
		for (int i = 0; i < sizeData; ++i) {
			++arrayOut[(int)data];
		}
	}
}

bool test() {
	return true;
}

int main() {
	setlocale(LC_ALL, "RUS");
	int arrayOut[128] = { 0 };
	printf("¬ведите название файла(с расширением), он будет считан, и будет выведено колличество различных символов из строки\n");
	char fileName[100] = { '\0' };
	int checkScan = scanf("%s", &fileName);

	while (checkScan != 1) {
		while (getchar() != '\n') {

		}
		checkScan = scanf("%s", &fileName);
	}
	scanFile(arrayOut, fileName);
	for (int i = 0; i < 128; ++i) {
		if (arrayOut[i] != 0) {
			printf("%c: %d", (char)i, arrayOut[i]);
		}
	}
}