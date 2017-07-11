//
// Created by carolinanery on 10/06/17.
//

#ifndef TREE_AVL_BITREE_H
#define TREE_AVL_BITREE_H

#include <stdlib.h>

/*AVL nodo da arvore*/
typedef struct Node {
    int conteudo;
    struct Node *left;
    struct Node *right;
    int altura;
} Node;

int max (int a, int b);
int altura(struct Node *N);
struct Node* newNode(int key);
struct Node *rightRotate(struct Node *n);
struct Node *leftRotate(struct Node *n);

int getFB (struct Node *N);

struct Node* insert(struct Node* node, int contudo);

struct Node *minValueNode(struct Node* node);
struct Node* deleteNode(struct Node* root, int contudo);

void liberarNode(struct Node *t);

void printTree(struct Node *root, int h);
#endif //TREE_AVL_BITREE_H
