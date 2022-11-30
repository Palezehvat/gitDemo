#pragma once
typedef struct HashTable HashTable;
typedef struct ElementsHashTable ElementsHashTable;

//Create hashTable
HashTable* createHashArray(int* errorCode, int size);

//Counting key by string for hash-table
int hashFunction(char string[], int size);

//Add to hash-table
void addToHashTable(HashTable* table, char string[], int* errorCode);