#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool test(void) {
	int errorCode = 0;
	HashTable* table = createHashArray(&errorCode, 4);
	if (errorCode == -1) {
		return false;
	}
	if (table == NULL) {
		return false;
	}
	char bufferFirst[4] = { 'a', 'b', 'c', '\0'};
	char bufferSecond[4] = { 'a', 'c', 'b', '\0'};
	addToHashTable(table, bufferFirst, &errorCode);
	if (errorCode == -1) {
		return false;
	}
	addToHashTable(table, bufferSecond, &errorCode);
	if (errorCode == -1) {
		return false;
	}
	char** buffer = (char**)malloc(2 * sizeof(char*));
	if (buffer == NULL) {
		return false;
	}
	buffer[0] = bufferFirst;
	buffer[1] = bufferSecond;
	bool testResult = ifAllInTableWithoutIdentical(table, buffer, 2);
	clearHashTable(table);
	free(buffer);
	return testResult;
}
//Resize - 2
//FillFacot - 1