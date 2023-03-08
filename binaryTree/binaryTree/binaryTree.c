#include "binaryTree.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Value {
    int key;
    char* value;
} Value;

typedef struct Node {
    Value value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(const int key, const char* value) {
    Node* temp = calloc(1, sizeof(Node));
    if (temp == NULL) {
        return NULL;
    }
    temp->value.key = key;
    temp->value.value = value;
}

Node* addToBinaryTree(Node* tree, const int key, const char* value) {
    if (tree == NULL) {
        tree = createNode(key, value);
        return tree;
    }

    Node* walker = tree;
    Node* prevWalker = NULL;

    while (walker != NULL) {
        if (walker->value.key == key) {
            free(walker->value.value);
            walker->value.value = value;
            return tree;
        } else if (walker->value.key > key) {
            prevWalker = walker;
            walker = walker->left;
        } else {
            prevWalker = walker;
            walker = walker->right;
        }
    }

    if (key > prevWalker->value.key) {
        prevWalker->right = createNode(key, value);
    } else {
        prevWalker->left = createNode(key, value);
    }
    return tree;
}

bool isKeyInTree(Node* tree, const int key) {
    return returnValueByKey(tree, key) != NULL;
}

void clearOneElement(Node* tree) {
    if (tree != NULL) {
        free(tree->value.value);
        free(tree);
    }
}

void toChangePointerByKey(Node* treeFirst, Node* treeSecond, int keySecond) {
    if (treeFirst->value.key < keySecond) {
        treeFirst->right = treeSecond;
    }
    else {
        treeFirst->left = treeSecond;
    }
}

Node* deleteNodeInTreeByKey(Node* tree, const int key) {
    if (tree == NULL) {
        return tree;
    }
    Node* walker = tree;
    Node* prevWalker = NULL;

    while (walker != NULL) {
        if (walker->value.key == key) {
            if (prevWalker == NULL) {
                if (walker->right != NULL) {
                    Node* newWalker = walker->right->left;
                    if (newWalker == NULL) {
                        tree = walker->right;
                        walker->right->left = walker->left;
                        clearOneElement(walker);
                        return tree;
                    }
                    while (newWalker->left != NULL) {
                        newWalker = newWalker->left;
                    }
                    tree = walker->right;
                    newWalker->left = walker->left;
                    clearOneElement(walker);
                    return tree;
                }
                else {
                    if (tree->left == NULL && tree->right == NULL) {
                        free(tree);
                        tree = NULL;
                        return tree;
                    }
                    tree = walker->left;
                    clearOneElement(walker);
                    return tree;
                }
                return tree;
            }
            if (walker->right != NULL) {
                Node* newWalker = walker->right->left;
                toChangePointerByKey(prevWalker, walker->right, key);
                if (newWalker == NULL) {
                    walker->right->left = walker->left;
                    clearOneElement(walker);
                    return tree;
                }
                while (newWalker->left != NULL) {
                    newWalker = newWalker->left;
                }
                newWalker->left = walker->left;
                clearOneElement(walker);
                return tree;
            } else {
                toChangePointerByKey(prevWalker, walker->left, key);
                clearOneElement(walker);
                return tree;
            }
        } else if (walker->value.key > key) {
            prevWalker = walker;
            walker = walker->left;
        } else {
            prevWalker = walker;
            walker = walker->right;
        }
    }
    return tree;
}

char* returnValueByKey(Node* tree, const int key) {
    if (tree == NULL) {
        return NULL;
    }
    Node* walker = tree;
    while (walker != NULL) {
        if (walker->value.key == key) {
            return walker->value.value;
        } else if (walker->value.key < key) {
            walker = walker->right;
        } else {
            walker = walker->left;
        }
    }
    return NULL;
}

void clearBinaryTree(Node* tree) {
    if (tree != NULL) {
        clearBinaryTree(tree->left);
        clearBinaryTree(tree->right);
        free(tree->value.value);
        free(tree);
    }
}