#pragma once
#include <stdbool.h>

typedef struct HashTable HashTable;

//Create hash-table
HashTable* createHashArray(int* errorCode, int size);

//Add to hash-table
void addToHashTable(HashTable* table, char string[], int* errorCode);

//Print hash-table
void printHashTable(HashTable* table);

//Clear hash-table
void clearHashTable(HashTable* table);

//find fill factor hash-table
double fillFactor(HashTable* table);

//Only for test
bool ifAllInTableWithoutIdentical(HashTable* table, char** buffer, int sizeBuffer);