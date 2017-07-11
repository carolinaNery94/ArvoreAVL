#include <stdio.h>
#include "arvore.h"

int main() {
    Node *raiz = NULL;
    int i;
    int op;
    int n, x;

    do {
        printf("\n1. Criar arvore: ");
        printf("\n2. Inserir elementos na arvore: ");
        printf("\n3. Deletar elementos da arvore:");
        printf("\n4. Imprimir a arvore: ");
        printf("\n5. Sair");
        printf("\n\nEscolha uma opção:");
        scanf("%d", &op);

        switch (op){
            case 1:
                printf("\nEntre com o numero de elementos:");
                scanf("%d", &n);
                printf("\nEntre com os elementos:");
                raiz = NULL;
                for (i = 0; i<n; i++){
                    scanf("%d", &x);
                    raiz = insert(raiz, x);
                }
                break;

            case 2:
                printf("\nEntre com o elemento que voce gostaria de inserir:");
                scanf("%d", &x);
                raiz = insert(raiz, x);
                break;

            case 3:
                printf("\nEntre com o elemento que voce gostaria de deletar: ");
                scanf("%d", &x);
                raiz = deleteNode(raiz, x);
                break;

            case 4:
                printf("\nImpressao da arvore\n");
                printTree(raiz, 0);
                break;
            default:
                break;
        }
    } while (op !=5);

    liberarNode(raiz);

    return 0;
}