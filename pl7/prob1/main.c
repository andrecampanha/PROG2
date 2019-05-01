#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"
#include "avl.h"

int main(int argc, char const *argv[])
{
    arvore_bst *bt = bst_nova();

    bst_insere(bt, "G");
    bst_insere(bt, "C");
    bst_insere(bt, "A");
    bst_insere(bt, "F");
    bst_insere(bt, "L");
    bst_insere(bt, "J");
    bst_insere(bt, "V");
    bst_insere(bt, "M");
    bst_insere(bt, "N");
    bst_insere(bt, "O");

    printf("Altura raiz: %d\n", bst_altura(bt->raiz));

    printf("Travessia em pré-ordem da árvore BST: ");
    bst_imprime(bt);

    bst_apaga(bt);

    arvore_avl *avl = avl_nova();

    avl_insere(avl, "G");
    avl_insere(avl, "C");
    avl_insere(avl, "A");
    avl_insere(avl, "F");
    avl_insere(avl, "L");
    avl_insere(avl, "J");
    avl_insere(avl, "V");
    avl_insere(avl, "M");
    avl_insere(avl, "N");
    avl_insere(avl, "O");

    printf("Altura raiz: %d\n", avl_altura(avl->raiz));

    printf("Travessia em pré-ordem da árvore AVL: ");
    avl_imprime(avl);

    avl_remove(avl, "N");
    
    printf("Travessia em pré-ordem da árvore AVL: ");
    avl_imprime(avl);

    avl_remove(avl, "V");

    printf("Travessia em pré-ordem da árvore AVL: ");
    avl_imprime(avl);

    avl_apaga(avl);
    return 0;
}
