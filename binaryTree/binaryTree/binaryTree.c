#include "binaryTree.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct value {
    int key;
    char* value;
} value;

typedef struct Node {
    value value;
    struct Node* left;
    struct Node* right;
} Node;

bool addToBinaryTree(Node* tree, int key, char* value) {
    if (tree == NULL) {
        Node* temp = calloc(1, sizeof(Node));
        if (temp == NULL) {
            return false;
        }
        temp->value.key = key;
        temp->value.value = value;
        tree = temp;
        return true;
    }
    Node* walker = tree;
    Node* prevWalker = NULL;

    while (walker != NULL) {
        if (walker->value.key == key) {
            walker->value.value = value;
            return true;
        } else if (walker->value.key > key) {
            prevWalker = walker;
            walker = walker->left;
        } else {
            prevWalker = walker;
            walker = walker->right;
        }
    }
    Node* temp = calloc(1, sizeof(Node));
    if (temp == NULL) {
        return false;
    }
    temp->value.key = key;
    temp->value.value = value;
    if (key > prevWalker->value.key) {
        prevWalker->right = temp;
    } else {
        prevWalker->left = temp;
    }
    return true;
}

bool isThereAKeyInTheTree(Node* tree, int key) {
    if (tree == NULL) {
        return false;
    }
    Node* walker = tree;
    while (walker != NULL) {
        if (walker->value.key == key) {
            return true;
        }
        else if (walker->value.key < key) {
            walker = walker->right;
        }
        else {
            walker = walker->left;
        }
    }
    return false;
}

bool deleteNodeInTreeByKey(Node* tree, int key) {
    if (tree == NULL) {
        return true;
    }
    Node* walker = tree;
    Node* prevWalker = NULL;

    while (walker != NULL) {
        if (walker->value.key == key) {
            if (prevWalker == NULL) {

                return true;
            }
            if (prevWalker->value.key < key) {
                if (walker->right != NULL) {
                    Node* newRight = walker->right;
                    Node* newLeft = walker->left;
                    Node* newWalker = newRight->left;
                    if (newWalker == NULL) {
                        prevWalker->right = newRight;
                        newRight->left = newLeft;
                        free(walker);
                        return true;
                    }
                    while (newWalker->left != NULL) {
                        newWalker = newWalker->left;
                    }
                    prevWalker->right = newRight;
                    newWalker->left = newLeft;
                    free(walker);
                    return true;
                } else {
                    prevWalker->right = walker->left;
                    free(walker);
                    return true;
                }
            } else {
                if (walker->right != NULL) {
                    Node* newRight = walker->right;
                    Node* newLeft = walker->left;
                    Node* newWalker = newRight->left;
                    if (newWalker == NULL) {
                        prevWalker->left = newRight;
                        newRight->left = newLeft;
                        free(walker);
                        return true;
                    }
                    while (newWalker->left != NULL) {
                        newWalker = newWalker->left;
                    }
                    prevWalker->left = newRight;
                    newWalker->left = newLeft;
                    free(walker);
                    return true;
                }
                else {
                    prevWalker->left = walker->left;
                    free(walker);
                    return true;
                }
            }
            return true;
        }
        else if (walker->value.key > key) {
            prevWalker = walker;
            walker = walker->left;
        }
        else {
            prevWalker = walker;
            walker = walker->right;
        }
    }
    return true;
}

char* returnValueByKey(Node* tree, int key) {
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
    if (tree->left == NULL && tree->right == NULL) {
        free(tree);
        return ;
    }
    clearBinaryTree(tree->left);
    clearBinaryTree(tree->right);
}