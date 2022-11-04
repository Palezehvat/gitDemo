#ifndef TREE_H
#define TREE_H

typedef struct Tree Tree;

//Создание дерева
Tree* createTree(void);

//Добавление в дерево элемента, состоящего из пустого int'а и непустого char'а
void addToTreeSymbol(Tree* tree, char symbol, int* errorCode);

//Добавление в дерево элемента, состоящего из непустого int'а и пустого char'а
void addToTreeNumber(Tree* tree, int number, int* errorCode);

#endif