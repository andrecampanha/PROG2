#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "market.h"

/* DEFINES E VARIAVEIS GLOBAIS UTEIS PARA OS TESTES */
#define MAX_CATEGNAME_LEN 100
#define N_CATEG 10
#define CAP_ALL_CATEG 3
#define VERBOSITY 0  // colocar a 1 se desejar imprimir mais detalhes sobre os testes

typedef struct {
    char name[MAX_CATEGNAME_LEN];
    int qty;
} e_categ;

typedef struct {
    e_categ *elem;
    int len, cap;
} vec_categ;


const char DEFAULT_FILE[32] = "armazem1.txt";

void avl_preordem(no_avl* no)
{
    if(no == NULL)
        return;

    printf("%s ", no->categ->categName);
    avl_preordem(no->esquerda);
    avl_preordem(no->direita);
}


e_categ *n_categ(vec_categ *vec, const char *categName)
{
    // Create if vec doesnt exist
    if(vec->elem == NULL)
    {
        vec->cap = 10;
        vec->len = 0;
        vec->elem = malloc(sizeof(e_categ) * vec->cap);
    }
    
    // Check if categ already exists
    e_categ *categ = NULL;
    for(int i = 0; i < vec->len; i++)
    {
        if(strcmp(vec->elem[i].name, categName) == 0)
        {
            categ = &vec->elem[i];
            break;
        }
    }

    if(!categ)
    {
        if(vec->len >= vec->elem->qty)
        {
            vec->cap*=2;
            vec->elem = realloc(vec->elem, sizeof(e_categ) * vec->cap);
        }
        strcpy(vec->elem[vec->len].name, categName);
        vec->elem[vec->len].qty = 0;
        vec->len++;
        categ = &vec->elem[vec->len - 1];
    }
    return categ;
}

arvore_avl *ler_ficheiro(const char *file_name)
{
    printf("A criar a AVL...\n");
    arvore_avl *avl = avl_nova();
    if(avl == NULL)
    {
        printf("ERRO: AVL não foi criada\n");
        return NULL;
    }
    printf("AVL criada\n\n");

    printf("A ler o ficheiro...\n");
    int errCount = 0;
    FILE *f = fopen(file_name, "r");
    if(!f)
    {
        printf("ERRO: ficheiro %s nao encontrado\n", file_name);
        return NULL;
    }

    char itemName[100], categName[MAX_CATEGNAME_LEN], expirationDate[11];
    int qty, itemsPerDay;
    elemento_t *elem;

    vec_categ vec;
    vec.elem = NULL;

    while(fscanf(f, "%s %s %d %d %s\n", itemName, categName, &qty, &itemsPerDay, expirationDate) == 5)
    {
        elem = elemento_novo(itemName, expirationDate, qty, itemsPerDay);
        if(elem == NULL)
        {
            printf("ERRO: elemento %s não foi criado\n", itemName);
            return NULL;
        }
        no_avl *no = avl_pesquisa(avl->raiz, categName);
        if(strcmp(itemName, "O_cao_que_desaparece") == 0)
        {
            int a = 0;
            a++;
        }
        e_categ *categ = n_categ(&vec, categName);

        int s = artigo_adiciona(avl, elem, categName, CAP_ALL_CATEG);
        if(s && categ->qty++ >= CAP_ALL_CATEG)
        {
            printf("ERRO: elemento %s foi inserido na categoria %s embora já não houvesse capacidade (%d/%d)\n", itemName, categName, categ->qty, CAP_ALL_CATEG);
            return NULL;
        }
        if(!s && categ->qty < CAP_ALL_CATEG)
        {
            printf("ERRO: elemento %s não foi inserido na categoria %s embora houvesse capacidade (%d/%d)\n", itemName, categName, categ->qty, CAP_ALL_CATEG);
            return NULL;
        }
        if(s && avl_pesquisa(avl->raiz, categName) == NULL)
        {
            printf("ERRO: a categoria %s nao foi introduzida na AVL\n", categName);
            return NULL;
        }
    }
    fclose(f);

    printf("Ficheiro lido e introduzido na AVL com sucesso!\n\n");

    free(vec.elem);

    return avl;
}

void montra(arvore_avl *avl, const char *categName)
{
    
}

int main(int argc, char const *argv[])
{
    const char *file_name = (argc > 1)? argv[1] : DEFAULT_FILE;

    arvore_avl *avl;
    if(!(avl = ler_ficheiro(file_name))) return 0;

    avl_preordem(avl->raiz);
    printf("\n");

    avl_apaga(avl);
    return 0;
}


