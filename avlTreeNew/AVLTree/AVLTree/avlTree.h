#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stdbool.h>

typedef struct Tree Tree;

// �������� ������
Tree* createTree(void);

// �������� ������
void clearTree(Tree* tree);

// ���������� ���� � ������
void addToTree(Tree* tree, const char* key, char* string);

// ���������� �������� �� �����
char* returnValueByKey(Tree* tree, const char* key);

// �������� ������� �����
bool isKeyInTree(Tree* tree, const char* key);

// �������� �������� �� �����
void deleteNodeInTreeByKey(Tree* tree, const char* key);

//�������� �� ������, ������ ��� ������
bool checkBalance(Tree* tree);
#endif