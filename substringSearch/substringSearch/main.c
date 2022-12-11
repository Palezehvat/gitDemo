#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char* getLine(int* lengthString, int* errorCode) {
	*lengthString = 0;
	int index = 1;
	char* string = (char*)malloc(sizeof(char));
	if (string == NULL) {
		*errorCode = -1;
		return NULL;
	}
	char symbol = getchar();
	while (symbol != '\n') {
		string[*lengthString] = symbol;
		++(*lengthString);
		if (*lengthString >= index) {
			index *= 2;
			char* copy = (char*)realloc(string, index * sizeof(char));
			if (copy == NULL) {
				*errorCode = -1;
				free(string);
				return NULL;
			}
			string = copy;
		}
		symbol = getchar();
	}
	if (string == NULL) {
		*errorCode = -1;
		return NULL;
	}
	string[*lengthString] = '\0';

	return string;
}

int* prefixFunction(const char* string) {
	int* prefixArray = calloc(strlen(string), sizeof(int));
	if (prefixArray == NULL) {
		return NULL;
	}
	prefixArray[0] = 0;
	size_t sizeString = strlen(string);
	for (size_t i = 1, j = 0; i < sizeString; ++i) {
		while (j > 0 && string[j] != string[i]) {
			j = prefixArray[j - 1];
		}
		if (string[i] == string[j]) {
			++j;
		}
		prefixArray[i] = j;
	}
	return prefixArray;
}

int findIndexSubstring(const char* string, const char* substring, int* errorCode) {
	size_t sizeString = strlen(string);
	size_t sizeSubstring = strlen(substring);
	int result = -1;
	if (sizeString == 0 || sizeSubstring == 0 || sizeString < sizeSubstring) {
		return -1;
	}
	int* prefixArray = prefixFunction(substring);
	for (int i = 0, j = 0; i < sizeString; ++i) {
		while (j > 0 && prefixArray[j] != prefixArray[i]) {
			j = prefixArray[j - 1];
		}
		if (prefixArray[j] == prefixArray[i]) {
			++j;
		}
		if (j == sizeSubstring) {
			free(prefixArray);
			return i - j + 1;
		}
	}
	free(prefixArray);
	return -1;
}

int workWithFile(const char* nameFile, int* errorCode, int sizeSubstring, const char* substring) {
	FILE* file;
	*errorCode = fopen_s(&file, nameFile, "r");
	if (*errorCode != 0 || file == NULL) {
		*errorCode = -1;
		return;
	}

	char buffer[400] = { '\0' };
	char copyText[200] = { '\0' };
	int steps = 1;
	size_t sizeBuffer = 0;
	size_t sizeCopyText = 0;
	while (fgets(copyText, 200, file) != NULL) {
		switch (steps)
		{
		case 1:
			strcpy(buffer, copyText);
			steps = 2;
			break;
		case 2:
			sizeBuffer = strlen(buffer);
			sizeCopyText = strlen(copyText);
			for (int i = sizeBuffer; i < sizeCopyText; ++i) {
				buffer[i] = copyText[i];
			}
			steps = 3;
			break;
		case 3:
			sizeBuffer = strlen(buffer);
			if (sizeBuffer >= 200) {
				int difference = sizeBuffer - 199;
				for (int i = sizeBuffer - 199; i < sizeBuffer; ++i) {
					buffer[i - difference] = buffer[i];
				}
			}
			sizeCopyText = strlen(copyText);
			for (int i = 0; i < copyText; ++i) {
				buffer[i + 200] = copyText[i];
			}
			break;
		}
		int index = findIndexSubstring(buffer, substring, errorCode);
		if (index != -1) {
			return index;
		}
		if (*errorCode != 0) {
			return -1;
		}
		memset(copyText, 0, 200);	
	}
}

int main() {
	printf("Input file name with extension\n");
	int errorCode = 0;
	int sizeFile = 0;
	const char* nameFile = getLine(&sizeFile, &errorCode);
	if (errorCode != 0) {
		printf("Error\n");
		return -1;
	}
	printf("Input substring. No more than 99 symbols\n");
	int sizeSubstring = 0;
	char* substring = getLine(&sizeSubstring, &errorCode);
	if (errorCode != 0 || substring == NULL) {
		printf("Error\n");
		return -1;
	}
	while (sizeSubstring > 100) {
		printf("No more than 99 symbols");
		free(substring);
		substring = getLine(&sizeSubstring, &errorCode);
		if (errorCode != 0 || substring == NULL) {
			printf("Error\n");
			return -1;
		}
	}
	int number = workWithFile(nameFile, &errorCode, sizeSubstring, substring);
	if (errorCode != 0) {
		printf("Error\n");
		return -1;
	}
	free(nameFile);
	free(substring);
	if (number != -1) {
		printf("%d\n", number);
	} else {
		printf("No occurrences found\n");
	}
}