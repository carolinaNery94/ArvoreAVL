#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"

/*método que retorna o máximo entre dois inteiros*/
int max (int a, int b){
    return (a > b)? a : b;
}

/*método que retorna a altura da árvore*/
int altura(struct Node *N){
    if (N == NULL)
        return 0;
    return N->altura;
}

/*método que cria um novo nodo*/
struct Node* newNode(int conteudo){
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));

    node->conteudo = conteudo;
    node->left = NULL;
    node->right = NULL;
    node->altura = 1;
    return (node);
}

/*método de rotação para a direita*/
struct Node *rightRotate(struct Node *n){
    struct Node *x = n->left;
    struct Node *T2 = x->right;

    x->right = n;
    n->left = T2;

    n->altura = max(altura(n->left), altura(n->right)) +1;
    x->altura = max(altura(x->left), altura(x->right)) +1;

    return x;
}

/*método de rotação para a esquerda*/
struct Node *leftRotate(struct Node *n){
    struct Node *y = n->right;
    struct Node *T2 = y->left;

    y->left = n;
    n->right = T2;

    n->altura = max(altura(n->left), altura(n->right))+1;
    y->altura = max(altura(y->left), altura(y->right))+1;

    return y;
}

/*método que retorna o valor do balanceamento*/
int getFB (struct Node *N){
    if (N == NULL)
        return 0;
    return altura(N->left) - altura(N->right);
}

/*método de inserção*/
struct Node* insert(struct Node* node, int contudo){
    if(node == NULL)
        return (newNode(contudo));

    if (contudo < node->conteudo) //conteudo que eu quero inserir menor que a raiz
        node->left = insert(node->left, contudo); //insere na esquerda

    else if (contudo > node->conteudo) //conteudo que eu quero inserir maior que a raiz
        node->right = insert(node->right, contudo); //insere na direita
    else
        return node; //se for igual, nada acontece

    node->altura = 1 + max(altura(node->left), altura(node->right)); //atualiza a altura do nodo

    //obtemos o fator de balanceamento do nós para ver se a árvore se tornou desbalanceada
    int balance = getFB(node);

    //se a arvore ficou desbalanceada nós temos 4 casos

    //caso1 inserção esquerda esquerda, uma rotação para direita
    if (balance > 1 && contudo < node->left->conteudo)
        return rightRotate(node);

    //caso2 inserção direita direita, uma rotação para esquerda
    if (balance < -1 && contudo > node->right->conteudo)
        return leftRotate(node);

    //caso3 inserção esquerda direita, uma rotação para esquerda + uma rotação para direita.
    if (balance > 1 && contudo > node->left->conteudo){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //caso4 inserção direita esquerda, uma rotação para direita + uma rotação para esquerda.
    if (balance < -1 && contudo < node->right->conteudo){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/*método que retorna o menor valor da esquerda daquele nó.
 * Dada uma árvore não vazia, devolva o nó com o valor mínimo encontrado nessa árvore.
 * a arvore não precisa ser toda percorrida.*/

struct Node *minValueNode(struct Node* node){
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

/*Função recursiva para excluir um nó. Retorna a raiz da subárvore modificada.
 * parametros: arvore que vai ser modificada e conteudo a ser excluido */

struct Node* deleteNode(struct Node* root, int contudo){
    if (root == NULL)
        return root;

    if (contudo < root->conteudo) //se o conteudo a ser removido for menor do que o conteudo corrente da arvore
        root->left = deleteNode(root->left, contudo); //então o conteudo a ser excluido fica na subárvore da esquerda

    else if (contudo > root->conteudo) //se o conteudo a ser removido for maior do que o conteudo corrente da arvore
        root->right = deleteNode(root->right, contudo); //então o conteudo a ser excluido fica na subarvore da direita

        //se o conteudo for igual raiz, então é a raiz a ser excluida
    else{
        //nó com apenas um filho.
        if ((root->left == NULL) || (root->right == NULL)){
            struct Node *temp = root->left ? root->left : root->right;

            //se não tiver filhos
            if (temp == NULL){
                temp = root;
                root = NULL;
                //caso com um filho, basta copiar os valores do filho.
            } else
                *root = *temp;
                free(temp);
        } else{
            // nó com dois filhos. Nesse caso, obtemos o sucessor menor na subárvore da direita
            struct Node* temp = minValueNode(root->right);
            //copiar os dados do sucessor para o nó
            root->conteudo = temp->conteudo;
            //excluir o nó
            root->right = deleteNode(root->right, temp->conteudo);
        }
    }
    //se a árvore tiver apenas um nó, retornar.
    if (root == NULL)
        return root;

    //ajustar a altura
    root->altura = 1 + max(altura(root->left), altura(root->right));

    int balance = getFB(root); //obter o fator de balanceamento, verificar se a árvore deslanaceou

    //se a árvore desbalanceou temos 4 casos:

    //caso1 esquerda esquerda
    if (balance > 1 && getFB(root->left) >= 0)
        return rightRotate(root); //uma rotação para a direita

    //caso2 esquerda direita
    if (balance > 1 && getFB(root->left) < 0){
        root->left = leftRotate(root->left); //uma rotação para esquerda + uma rotação para direita
        return rightRotate(root);
    }

    //caso3 direita direita
    if (balance < -1 && getFB(root->right) <= 0)
        return leftRotate(root); //rotacao para a esquerda

    //caso4 direita esquerda
    if (balance < -1 && getFB(root->right) > 0){
        root->right = rightRotate(root->right); //uma rotação para direita + uma rotação para esquerda
        return leftRotate(root);
    }

    return root;
}

//método que imprime a árvore.
void printTree(struct Node *root, int h){
    int i;
    if (root != NULL){

        printTree(root->right, h+1);
        for (i = 0; i < h; i++)
            printf("   ");
        printf("%d\n", root->conteudo);
        printTree(root->left, h+1);
    }
}

//método para liberar a árvore
void liberarNode(struct Node *t){
    if (t != NULL){
        liberarNode(t->left);
        liberarNode(t->right);
        free(t);
    }
}