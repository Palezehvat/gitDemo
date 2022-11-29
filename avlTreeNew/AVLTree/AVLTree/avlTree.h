#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stdbool.h>

typedef struct Tree Tree;

//Создание дерева
Tree* createTree(void);

//Удаление дерева
void clearTree(Tree* tree);

//Добавление узла к дереву
void addToTree(Tree* tree, int key, char* string);

//Возвращает значение по ключу
char* returnValueByKey(Tree* tree, int key);

//Проверка наличия ключа
bool isKeyInTree(Tree* tree, int key);

//Удаление элемента по ключу
void deleteNodeInTreeByKey(Tree* tree, int key, const bool ifUseFile);
#endif