#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    char number[100];
    char name[100];
    struct Node* next;
    struct Node* prev;
} Node;

struct List {
    Node* head;
    Node* tail;
};

bool isEmpty(List* list) {
    return list->head == NULL;
}

//смотрит по индексам два элемента, возвращает значение i, если элемент с индексом i больше, чем элемент с индексом j, возвращает значение j в другом случие
int isWhichBigger(List* list, Node* i, Node* j, int numberOrName) {
    Node* walkerFirst = list->head;
    int iWalker = 0;
    while (iWalker < i&& walkerFirst->next != NULL) {
        ++iWalker;
        walkerFirst = walkerFirst->next;
    }
    Node* walkerSecond = list->head;
    int jWalker = 0;
    while (jWalker < j&& walkerSecond->next != NULL) {
        ++jWalker;
        walkerSecond = walkerSecond->next;
    }
    if (numberOrName == 0) {
        return strcmp(i->name, j->name) > 0 ? i : j;
    }
    else {
        return strcmp(i->number, j->number) > 0 ? i : j;
    }
}

void toList(List* list, List* listCopy, Node* positionList, Node* positionListCopy, int numberOrName, int copyOrMain) {
    if (copyOrMain == 0) {
        strcpy(positionListCopy->name, positionList->name);
        strcpy(positionListCopy->number, positionList->number);
    }
    else {
        strcpy(positionList->name, positionListCopy->name);
        strcpy(positionList->number, positionListCopy->number);
    }
}

Node* findMiddle(Node* with, Node* to) {
    Node* walkerWith = with;
    Node* walkerTo = to;
    while (walkerWith != walkerTo || walkerWith->next != walkerTo) {
        walkerWith = walkerWith->next;
        walkerTo = walkerTo->prev;
    }
    return walkerWith;
}

void mergeSortOriginal(Node* with, Node* to, List* list, List* listCopy, int numberOrName) {
    if (to <= with) {
        return;
    }

    Node* middle = findMiddle(with, to);

    mergeSortOriginal(with, middle, list, listCopy, numberOrName);
    mergeSortOriginal(middle + 1, to, list, listCopy, numberOrName);

    Node* i = with;
    Node* j = middle + 1;
    Node* l = with;
    while (i != j) {
        if (i == middle + 1) {
            toList(list, listCopy, j, l, numberOrName, 0);
            j = j->next;
        }
        else if (j == to + 1) {
            toList(list, listCopy, i, l, numberOrName, 0);
            i = i->next;
        }
        else if (isWhichBigger(list, i, j, numberOrName) == j) {
            toList(list, listCopy, i, l, numberOrName, 0);
            i = i->next;
        }
        else {
            toList(list, listCopy, j, l, numberOrName, 0);
            j = j->next;
        }
        l = l->next;
    }
    Node* k = with;
    while (k <= to) {
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
    mergeSortOriginal(list->head, list->tail, list, listCopy, numberOrName);
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
        newNode->prev = list->tail;
        list->head = newNode;
        list->tail = newNode;
        return 0;
    }

    list->tail->next = newNode;
    newNode->prev = list->tail;
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