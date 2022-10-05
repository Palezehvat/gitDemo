#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int findCommentsInFile(char bufferComments[100][100]) {
	FILE* file = fopen("textWithComments.txt", "r");
	if (file == NULL) {
		printf("Файл не найден!");
		return -1;
	}
	int i = 0;
	char data[100] = { '\0' };
	int sizeBuffer = 0;
	//printf("%d", fscanf(file, "%s", data));
	while (fscanf(file, "%s", data) == 1){
		if (data[0] == ';') {
			size_t sizeData = strlen(data);
			bufferComments[sizeBuffer][0] = ';';
			int j = 1;
			while (data[j - 1] != '\\' && data[j] != 'n') {
				bufferComments[sizeBuffer][j] = data[j];
				++j;
			}
			bufferComments[sizeBuffer][j] = 'n';
			++sizeBuffer;
		}
		++i;
	}

	fclose(file);
	return sizeBuffer;
}

int main() {
	setlocale(LC_ALL, "RUS");
	char bufferComments[100][100] = {'\0'};
	int sizeBuffer = findCommentsInFile(bufferComments);
	for (int i = 0; i < sizeBuffer; ++i) {
		printf("%s\n", bufferComments[i]);
	}
}