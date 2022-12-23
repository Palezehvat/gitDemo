#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    char number[100];
    char name[100];
    struct Node* next;
} Node;

struct List {
    Node* head;
    Node* tail;
};

bool isEmpty(List* list) {
    return list->head == NULL;
}

//������� �� �������� ��� ��������, ���������� �������� i, ���� ������� � �������� i ������, ��� ������� � �������� j, ���������� �������� j � ������ ������
int isWhichBigger(List* list, int i, int j, int numberOrName) {
    Node* walkerFirst = list->head;
    int iWalker = 0;
    while (iWalker < i && walkerFirst->next != NULL) {
        ++iWalker;
        walkerFirst = walkerFirst->next;
    }
    Node* walkerSecond = list->head;
    int jWalker = 0;
    while (jWalker < j && walkerSecond->next != NULL) {
        ++jWalker;
        walkerSecond = walkerSecond->next;
    }
    if (numberOrName == 0) {
        return strcmp(walkerFirst->name, walkerSecond->name) > 0 ? i : j;
    }
    else {
        return strcmp(walkerFirst->number, walkerSecond->number) > 0 ? i : j;
    }
}

void toList(List* list, List* listCopy, int positionList, int positionListCopy, int numberOrName, int copyOrMain) {
    Node* walkerCopy = listCopy->head;
    int i = 0;
    while (i < positionListCopy && walkerCopy->next != NULL) {
        walkerCopy = walkerCopy->next;
        ++i;
    }

    Node* walker = list->head;
    int j = 0;
    while (j < positionList && walker->next != NULL) {
        walker = walker->next;
        ++j;
    }

    if (copyOrMain == 0) {
        strcpy(walkerCopy->name, walker->name);
        strcpy(walkerCopy->number, walker->number);
    }
    else {
        strcpy(walker->name, walkerCopy->name);
        strcpy(walker->number, walkerCopy->number);
    }
}

void mergeSortOriginal(int with, int to, List* list, List* listCopy, int numberOrName) {
    if (to <= with) {
        return;
    }

    int middle = (with + to) / 2;
    mergeSortOriginal (with, middle, list, listCopy, numberOrName);
    mergeSortOriginal (middle + 1, to, list, listCopy, numberOrName);

    int i = with;
    int j = middle + 1;
    for (int l = with; l <= to; ++l) {
        if (i == middle + 1) {
            toList(list, listCopy, j, l, numberOrName, 0);
            ++j;
        }
        else if (j == to + 1) {
            toList(list, listCopy, i, l, numberOrName, 0);
            ++i;
        }
        else if (isWhichBigger(list, i, j, numberOrName) == j) {
            toList(list, listCopy, i, l, numberOrName, 0);
            ++i;
        }
        else {
            toList(list, listCopy, j, l, numberOrName, 0);
            ++j;
        }
    }
    for (int k = with; k <= to; ++k) {
        toList(list, listCopy, k, k, numberOrName, 1);
    }
}

void mergeSort(int size, List* list, int numberOrName) {
    int i = 0;
    List* listCopy = createList();
    while (i < size) {
        addRecord(listCopy, NULL, NULL);
        ++i;
    }
    mergeSortOriginal(0, size - 1, list, listCopy, numberOrName);
}

int addRecord(List* list, char name[], char number[]) {
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        clear(&list);
        return -1;
    }
    if (name != NULL && number != NULL) {
        size_t sizeName = strlen(name);
        memset(newNode->name, 0, strlen(newNode->name));
        strncpy(newNode->name, name, sizeName);

        size_t sizeNumber = strlen(number);
        memset(newNode->number, 0, strlen(newNode->number));
        strncpy(newNode->number, number, sizeNumber);
    }
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        return 0;
    }

    list->tail->next = newNode;

    list->tail = newNode;
    return 0;
}

List* createList(void) {
    List* list = calloc(1, sizeof(List));
    return list;
}

bool isSorted(List* list, int numberOrName) {
    if (list->head == NULL || list->head->next == NULL) {
        return true;
    }
    Node* walker = list->head->next;
    int i = 1;
    while (walker->next != NULL) {
        if (isWhichBigger(list, i - 1, i, numberOrName) == i - 1) {
            return false;
        }
        walker = walker->next;
        ++i;
    }
    return true;
}

void printList(List* list) {
    if (list->head == NULL) {
        return;
    }
    Node* walker = list->head;
    while (walker != NULL) {
        printf("%s - %s\n", walker->name, walker->number);
        walker = walker->next;
    }
}

void clear(List** list) {
    if ((*list)->head == NULL) {
        return;
    }
    Node* walker = (*list)->head;
    while ((*list)->head != NULL) {
        if ((*list)->head->next == NULL) {
            free((*list)->head);
            free(list);
            return;
        }
        walker = (*list)->head;
        while (walker->next->next != NULL) {
            walker = walker->next;
        }
        free(walker->next);
        walker->next = NULL;
    }
    free(*list);
}