#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "avl.h"
#include "bst.h"

#define $(FUNC) (void* (*)(void *))FUNC

void *measure(void* (*func)(void *file), void *arg)
{
    clock_t inicio, fim;
    double tempo;
    inicio = clock();
    void *val = func(arg);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("t = %lfs\n", tempo);

    return val;
}

arvore_bst *bst_read(FILE *fin)
{
    arvore_bst *bst = bst_nova();
    char str[500];

    long long c = 0;

    while(fgets(str, 500, fin) != NULL)
    {
        //if(c % 1000 == 0) fprintf(stderr, "%lld\n", c);
        str[strlen(str) - 1] = '\0';
        if(bst_insere(bst, str) == -1) 
        {
            bst_apaga(bst);
            return NULL;
        }
        c++;

    }

    return bst;
}

arvore_avl *avl_read(FILE *fin)
{
    arvore_avl *avl = avl_nova();
    char str[500];

    while(fgets(str, 500, fin) != NULL)
    {
        str[strlen(str) - 1] = '\0';
        if(avl_insere(avl, str) == -1) 
        {
            avl_apaga(avl);
            return NULL;
        }
    }

    return avl;
}

void* bst_pesq(arvore_bst *bst)
{
    bst_pesquisa(bst, "Zywiec,Poland");
    return NULL;
}

void* avl_pesq(arvore_avl *avl)
{
    avl_pesquisa(avl, "Zywiec,Poland");
    return NULL;
}

int main()
{
    FILE *f_cidades = fopen("cidades.txt", "r");

    if(f_cidades == NULL)
    {
        printf("Erro a abrir os ficheiros!\n");
        return 0;
    }

    printf("Leitura para bst: ");
    arvore_bst *bst = measure($(bst_read), f_cidades);
    fseek(f_cidades, 0, SEEK_SET);
    printf("Leitura para avl: ");
    arvore_avl *avl = measure($(avl_read), f_cidades);


    printf("Pesquisa bst: ");
    measure($(bst_pesq), bst);
    printf("Pesquisa avl: ");
    measure($(avl_pesq), avl);

    bst_apaga(bst);
    avl_apaga(avl);
    
    printf("\n\n==== Sorted ====\n\n");

    FILE *f_cidades_sorted = fopen("cidades_sorted.txt", "r");

    if(f_cidades_sorted == NULL)
    {
        printf("Erro a abrir os ficheiros!\n");
        return 0;
    }
    
    printf("Leitura para bst: ");
    bst = measure($(bst_read), f_cidades_sorted);
    /*fseek(f_cidades_sorted, 0, SEEK_SET);
    printf("Leitura para avl: ");
    avl = measure($(avl_read), f_cidades_sorted);*/


    /*printf("Pesquisa bst: ");
    measure($(bst_pesq), bst);
    printf("Pesquisa avl: ");
    measure($(avl_pesq), avl);*/


    bst_apaga(bst);
    avl_apaga(avl);

    fclose(f_cidades);
    fclose(f_cidades_sorted);
    return 0;
}
