#include "list.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Enter a more appropriate hash table size\n");
	int size = 0;
	int checkScanf = scanf("%d", &size);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}
		printf("ERROR\n");
		checkScanf = scanf("%d", &size);
	}
	printf("Print file name with its extension\n");
	char fileName[100] = { '\0' };
	checkScanf = scanf("%s", &fileName);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}
		printf("ERROR\n");
		checkScanf = scanf("%s", &fileName);
	}
	int errorCode = 0;
	HashTable* table = createHashArray(&errorCode, size);
	if (errorCode == -1) {
		printf("Memmory error\n");
		return -1;
	}
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Mistake!");
		return -1;
	}
	char data[100] = { '\0' };
	while (fscanf(file, "%s", data) == 1) {
		addToHashTable(table, data, &errorCode);
		if (errorCode == -1) {
			printf("Memmory error\n");
			return -1;
		}
	}
	fclose(file);
	printHashTable(table);
}