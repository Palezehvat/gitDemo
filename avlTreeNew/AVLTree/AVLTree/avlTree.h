#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stdbool.h>

typedef struct Tree Tree;

// Создание дерева
Tree* createTree(void);

// Удаление дерева
void clearTree(Tree* tree);

// Добавление узла к дереву
void addToTree(Tree* tree, const char* key, char* string);

// Возвращает значение по ключу
char* returnValueByKey(Tree* tree, const char* key);

// Проверка наличия ключа
bool isKeyInTree(Tree* tree, const char* key);

// Удаление элемента по ключу
void deleteNodeInTreeByKey(Tree* tree, const char* key);

//Проверка на баланс, только для тестов
bool checkBalance(Tree* tree);
#endif