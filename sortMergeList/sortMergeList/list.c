#include "list.h"
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    char number[100];
    char name[100];
    struct Node* next;
} Node;

struct List {
    Node* head;
};

bool isEmpty(List* list) {
    return list->head == NULL;
}

void mergeSortByName(List* list, int size) {

}

void mergeSortByNumber(List* list, int size) {


}

int addRecord(List* list, char name[], char number[]) {
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        return -1;
    }
    size_t sizeName = strlen(name);
    memset(newNode->name, 0, strlen(newNode->name));
    strncpy(newNode->name, name, sizeName);

    size_t sizeNumber = strlen(number);
    memset(newNode->number, 0, strlen(newNode->number));
    strncpy(newNode->number, number, sizeNumber);

    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        return ;
    }

    Node* walker = list->head;
    while (walker->next != NULL) {
        walker = walker->next;
    }
    walker->next = newNode;
    
}

List* createList(void) {
    List* list = calloc(1, sizeof(List));
    return list;
}

bool isSortedByNumber(List* list) {
    if (list->head == NULL || list->head->next == NULL) {
        return true;
    }
    Node* walker = list->head;
    char number[100] = { '\0' };
    strncpy(number, walker->number, strlen(walker->number));
    walker = walker->next;
    while (walker->next != NULL) {
        size_t sizeNumber = strlen(number);
        size_t sizeListNumber = strlen(walker->number);
        int i = 0;
        while (i < sizeNumber && i < sizeListNumber) {
            if (number[i] > walker->number[i]) {
                return false;
            } else if (number[i] < walker->number[i]) {
                break;
            }
        }
        memset(number, 0, strlen(number));
        strncpy(number, walker, strlen(walker->number));
        walker = walker->next;
    }
    return true;
}