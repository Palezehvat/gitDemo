#include "KMP.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
		while (j > 0 && substring[j] != string[i]) {
			j = prefixArray[j - 1];
		}
		if (substring[j] == string[i]) {
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
