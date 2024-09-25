#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

int scanOne();

bool readFromFileAndSort(const char* fileName, int numberOrName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("������! ");
        return false;
    }

    List* list = createList();

    char letter = 0;
    char name[100] = { '\0' };
    char number[100] = { '\0' };
    char buffer[100] = { '\0' };
    int stringInfile = 0;
    int size = 0;
    while (fscanf(file, "%s", buffer) == 1) {
        size_t sizeBuffer = strlen(buffer);
        size_t i = 0;
        if (stringInfile == 0) {
            while (i < sizeBuffer) {
                name[i] = buffer[i];
                ++i;
            }
        }
        if (stringInfile == 2) {
            while (i < sizeBuffer) {
                number[i] = buffer[i];
                ++i;
            }
            if (addRecord(list, name, number) != 0) {
                clear(&list);
                return false;
            }
            memset(name, 0, strlen(name));
            memset(number, 0, strlen(number));
            stringInfile = -1;
        }
        ++stringInfile;
        ++size;
    }
    fclose(file);
    size /= 3;

    mergeSort(size, list, numberOrName);

    if (strcmp(fileName, "test.txt") == 0) {
        return isSorted(list, numberOrName);
    }

    printList(list);
    clear(list);
    return true;
}

bool test(void) {
    return readFromFileAndSort("test.txt", 1);
}

int main() {
    setlocale(LC_ALL, "RUS");
    if (test()) {
        printf("���� ������ �������!\n");
    }
    else {
        printf("������...\n");
        return -1;
    }
    char fileName[100] = { '\0' };
    printf("������� ��� �����, � ��� ����������� (������ �������: test.txt)\n");
    int checkScan = scanf("%s", &fileName);

    while (strcmp(fileName, "test.txt") == 0 || checkScan != 1) {
        while (getchar() != '\n') {
        }
        printf("������... �������� �� ����� test.txt\n");
        checkScan = scanf("%s", &fileName);
    }
    printf("������� �� ���� ����������� (0 - �� �����, 1 - �� ������)\n");
    int sortByNameOrNumber = scanOne();
    while (sortByNameOrNumber != 0 && sortByNameOrNumber != 1) {
        printf("������� ������� ������������...\n");
        sortByNameOrNumber = scanOne();
    }
    if (!readFromFileAndSort(fileName, sortByNameOrNumber)) {
        printf("������ � ������...\n");
    }
}

int scanOne() {
    int number = 0;
    int checkScanf = scanf("%d", &number);

    while (checkScanf != 1) {
        while (getchar() != '\n') {
        }

        printf("������...\n");
        checkScanf = scanf("%d", &number);
    }

    return number;
}