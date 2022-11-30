#include "hash.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ElementsHashTable {
    struct List* list;
};

typedef struct HashTable {
    struct ElementsHashTable** arrayHash;
    int hashSize;
};

HashTable* createHashArray(int* errorCode, int size) {
    HashTable* table = calloc(1, sizeof(HashTable));
    if (table == NULL) {
        *errorCode = -1;
        return NULL;
    }
    table->hashSize = size;
    table->arrayHash = (ElementsHashTable**)malloc(size * sizeof(ElementsHashTable*));
    if (table->arrayHash == NULL) {
        *errorCode = -1;
        return;
    }
    for (int i = 0; i < size; ++i) {
        table->arrayHash[i] = (ElementsHashTable*)malloc(1 * sizeof(ElementsHashTable));
        if (table->arrayHash[i] == NULL) {
            *errorCode = -1;
            return NULL;
        }
        table->arrayHash[i]->list = NULL;
    }
    return table;
}

int fastPow(int number, int degree) {
    if (degree < 0) {
        return 1.0 / fastPow(number, abs(degree));
    }
    if (degree == 0) {
        return 1;
    }
    if (degree % 2 == 0) {
        const int copyElement = fastPow(number, degree / 2);
        return copyElement * copyElement;
    }
    return fastPow(number, degree - 1) * number;
}

int hashFunction(char string[], int size) {
    int result = 0;
    int simpleNumber = 7;
    int neededNumber = fastPow(simpleNumber, (int)strlen(string) - 1);
    for (int i = 0; string[i] != '\0'; ++i) {
        result += string[i] * neededNumber;
        neededNumber /= simpleNumber;
    }
    return result % size;
}

void addToHashTable(HashTable* table, char string[], int* errorCode) {
    int index = hashFunction(string, table->hashSize);
    if (table->arrayHash[index]->list == NULL) {
        table->arrayHash[index]->list = createList(errorCode);
        if (*errorCode == -1) {
            return;
        }
        insertToList(table->arrayHash[index]->list, string ,errorCode);
    } else {
        insertToList(table->arrayHash[index]->list, string, errorCode);
    }
}

void printHashTable(HashTable* table) {
    if (table == NULL || table->arrayHash == NULL) {
        return;
    }
    for (int i = 0; i < table->hashSize; ++i) {
        if (table->arrayHash[i]->list != NULL) {
            printf("%d)", i);
            printList(table->arrayHash[i]->list);
        } else {
            printf("%d)\n", i);
        }
    }
}