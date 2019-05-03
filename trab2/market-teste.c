/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "market.h"

/* DEFINES E VARIAVEIS GLOBAIS UTEIS PARA OS TESTES */
#define MAX_CATEGNAME_LEN 100
#define N_CATEG 10
#define CAP_ALL_CATEG 3
#define VERBOSITY 1  // colocar a 1 se desejar imprimir mais detalhes sobre os testes

const char DEFAULT_FILE[32] = "armazem.txt";
const char CATEGORIES[N_CATEG][MAX_CATEGNAME_LEN] = {
    "frescos",
    "fresquissimos",
    "peixaria",
    "livros",
    "beleza",
    "puericultura",
    "charcutaria",
    "laticinios",
    "padaria",
    "ferramentas"
};
/* ================================================= */

/* VERIFICACOES IMPLEMENTADAS */
int verifica_elemento_novo(elemento_t **elem, const char* nameItem, const char* expDate, int qty, int sellRate)
{
    *elem = elemento_novo(nameItem, expDate, qty, sellRate);
    if(!(*elem))
    {
        printf("...verifica_elemento_novo: elemento novo e' NULL (ERRO)\n");
        return -1;
    }
    else
        printf("...verifica_elemento_novo: elemento novo nao e' NULL (ok)\n");


    if(strcmp((*elem)->nameItem, nameItem))
    {
        printf("...verifica_elemento_novo: nameItem do novo elemento (= %s) e' diferente do esperado (= %s) (ERRO)", (*elem)->nameItem, nameItem);
        return -1;
    }
    else
        printf("...verifica_elemento_novo: nameItem coincide com o esperado (= %s) (ok)\n", nameItem);

    return 0;
}

int verifica_metrica(elemento_t *elem)
{
    float metrica = calcMetrica(elem);
    if(metrica <= 0. || metrica >= 1.)
    {
        printf("...verifica_metrica: metrica retornada (= %f) nao esta' em (0, 1) (ERRO)\n", metrica);
        return -1;
    }
    else
        printf("...verifica_metrica: metrica retornada (= %f) esta' no intervalo (0, 1) (ok)\n", metrica);

    return 0;
}

int verifica_heap_nova(heap **h, int capacidade)
{
    *h = heap_nova(capacidade);
    if(!(*h))
    {
        printf("...verifica_heap_nova: heap nova e' NULL (ERRO)\n");
        return -1;
    }
    else
        printf("...verifica_heap_nova: heap nova nao e' NULL (ok)\n");

    if((*h)->tamanho != 0)
    {
        printf("...verifica_heap_nova: tamanho da heap (= %d) nao e' 0 (ERRO)\n", (*h)->tamanho);
        return -1;
    }
    else
        printf("...verifica_heap_nova: tamanho da heap nova e' 0 (ok)\n");

    return 0;
}

int verifica_heap_remove(heap *h)
{
    int tamanho_ini = h->tamanho;
    elemento_t *elem = heap_remove(h);
    if(tamanho_ini > 0)
    {
        if(!elem)
        {
            printf("...verifica_heap_remove: elemento retornado e' NULL (ERRO)\n");
            return -1;
        }
        else
            printf("...verifica_heap_remove: elemento retornado nao e' NULL (ok)\n");
        if(h->tamanho == tamanho_ini)
        {
            printf("...verifica_heap_remove: tamanho da heap (= %d) manteve-se (ERRO)\n", tamanho_ini);
            return -1;
        }
        else
            printf("...novo tamanho da heap e' %d (ok)\n", h->tamanho);

        elemento_apaga(elem);
        elem = NULL;
    }

    return 0;
}

int verifica_avl_insere(arvore_avl *avl, category_t* categ)
{
    avl->raiz = avl_insere(avl->raiz , categ);
    if(!avl->raiz)
    {
        printf("...verifica_avl_insere: novo no' e' NULL (ERRO)\n");
        return -1;
    }
    else
        printf("...verifica_avl_insere: novo no' nao e' NULL (ok)\n");
    if(!(avl->raiz->categ))
    {
        printf("...verifica_avl_insere: categoria do no' e' NULL (ERRO)\n");
        return -1;
    }
    else
        printf("...verifica_avl_insere: categoria do no' nao e' NULL (ok)\n");

    return 0;
}

int verifica_avl_pesquisa(arvore_avl *avl)
{
    if(!avl || !avl->raiz || !avl->raiz->categ || !avl->raiz->categ->categName)
    {
        printf("...verifica_avl_pesquisa: erro estrutural na arvore AVL (dependencias sao NULL) (ERRO)\n");
        return -1;
    }
    char categQuery[MAX_CATEGNAME_LEN];
    strcpy(categQuery, avl->raiz->categ->categName);

    no_avl *resultado = avl_pesquisa(avl->raiz, categQuery);
    if(!resultado)
    {
        printf("...verifica_avl_pesquisa: categoria pesquisada (= %s) nao encontrada (retornou NULL) (ERRO)\n", categQuery);
        return -1;
    }
    else
        printf("...verifica_avl_pesquisa: pesquisa nao retornou NULL (ok)\n");

    if(strcmp(resultado->categ->categName, categQuery))
    {
        printf("...verifica_avl_pesquisa: nome da categoria retornado (= %s) diferente do pesquisado (= %s)) (ERRO)\n", resultado->categ->categName, categQuery);
        return -1;
    }
    else
        printf("...verifica_avl_pesquisa: nome da categoria retornada (= %s) coincide com o pesquisado (ok)\n", categQuery);

    return 0;
}

int verifica_artigo_adiciona(arvore_avl *avl, elemento_t *elem,  char *categName, int capCateg, int itemCount, int verbose)
{
    if(!avl->raiz)
    {
        artigo_adiciona(avl, elem, categName, capCateg);
        if(!avl->raiz)
        {
            printf("...verifica_artigo_adiciona: AVL continua vazia apos insercao de artigo (%s, %s) (ERRO)\n", elem->nameItem, categName);
            elemento_apaga(elem);
            return -1;
        }
        else if(verbose)
            printf("...verifica_artigo_adiciona: raiz da AVL nao e' NULL apos insercao de artigo (%s, %s) (ok)\n", elem->nameItem, categName);

    }
    else if(itemCount < capCateg)
    {
        if(artigo_adiciona(avl, elem, categName, capCateg) == 0)
        {
            printf("...verifica_artigo_adiciona: artigo_adiciona (%s, %s) retornou 0 (ERRO)\n", elem->nameItem, categName);
            return -1;
        }
        else if(verbose)
            printf("...verifica_artigo_adiciona: artigo_adiciona (%s, %s) retornou 1 (ok)\n", elem->nameItem, categName);
    }
    else
    {
        if(artigo_adiciona(avl, elem, categName, capCateg) == 1)
        {
            printf("...verifica_artigo_adiciona: capacidade excedida e artigo_adiciona (%s, %s) retornou 1 (ERRO)\n", elem->nameItem, categName);
            return -1;
        }
        else
        {
            if(verbose)
                printf("...verifica_artigo_adiciona: artigo_adiciona (%s, %s) retornou 0 quando nao ha espaco livre na heap (ok)\n", elem->nameItem, categName);
            elemento_apaga(elem);
            elem = NULL;
        }
    }

    return 0;
}

int verifica_criar_montra(arvore_avl *avl, char *categName, int numPorItem, int totalItens, int tamanhoEsp)
{
    if(!avl || !avl->raiz || !avl->raiz->categ || !avl->raiz->categ->categName)
    {
        printf("...verifica_criar_montra: erro estrutural na arvore AVL (atributos sao NULL) (ERRO)\n");
        return -1;
    }
    int array_tamanho = -1;
    elemento_t **itens = criar_montra(avl, categName, numPorItem, totalItens, &array_tamanho);
    if(itens)
    {
        for(int i = 0; i < array_tamanho; i++)
        {
            elemento_apaga(itens[i]);
            itens[i] = NULL;
        }
        free(itens);
        itens = NULL;
    }

    if(array_tamanho != tamanhoEsp)
    {
        printf("...verifica_criar_montra:: tamanho do array retornado (= %d) diferente do esperado (= %d) (ERRO)\n", array_tamanho, tamanhoEsp);
        return -1;
    }
    else
        printf("...tamanho do array retornado coincide com o esperado (= %d) (ok)\n", array_tamanho);

    return 0;
}
/* ================================================= */


/* DEFINICAO DOS CENARIOS DE TESTE */
int teste_elemento_novo_e_metrica(const char *file_name)
{
    printf("teste_elemento_novo_e_metrica iniciado...\n");
    int errCount = 0;
    FILE *f = fopen(file_name, "r");
    if(!f)
    {
        printf("ERRO: ficheiro %s nao encontrado\n", file_name);
        return 999;
    }

    char itemName[100], categName[MAX_CATEGNAME_LEN], expirationDate[11];
    int qty, itemsPerDay;

    fscanf(f, "%s %s %d %d %s\n",
           itemName, categName, &qty, &itemsPerDay, expirationDate);
    fclose(f);

    elemento_t *item;
    if(verifica_elemento_novo(&item, itemName, expirationDate, qty, itemsPerDay) == -1)
        errCount++;

    if(verifica_metrica(item) == -1)
        errCount++;

    elemento_apaga(item);
    item = NULL;

    return errCount;
}

int teste_heap(const char* file_name)
{
    printf("teste_heap iniciado...\n");
    int errCount = 0;
    FILE *f = fopen(file_name, "r");
    if(!f)
    {
        printf("ERRO: ficheiro %s nao encontrado\n", file_name);
        return 999;
    }

    char itemName[100], categName[MAX_CATEGNAME_LEN], expirationDate[11];
    int qty, itemsPerDay;

    fscanf(f, "%s %s %d %d %s\n",
           itemName, categName, &qty, &itemsPerDay, expirationDate);
    fclose(f);

    heap *itemHeap;
    if(verifica_heap_nova(&itemHeap, 1) == -1)
    {
        errCount++;
        return errCount;
    }

    elemento_t *item = elemento_novo(itemName, expirationDate, qty, itemsPerDay);
    heap_insere(itemHeap, item);

    if(verifica_heap_remove(itemHeap) == -1)
        errCount++;

    heap_apaga(itemHeap);
    itemHeap = NULL;

    return errCount;
}

int teste_avl(const char* file_name)
{
    printf("teste_avl iniciado...\n");
    int errCount = 0;
    FILE *f = fopen(file_name, "r");
    if(!f)
    {
        printf("ERRO: ficheiro %s nao encontrado\n", file_name);
        return 999;
    }
    arvore_avl *categAvl = avl_nova();
    if(!categAvl) return -1;

    char itemName[100], categName[MAX_CATEGNAME_LEN], expirationDate[11];
    int qty, itemsPerDay;

    fscanf(f, "%s %s %d %d %s\n",
           itemName, categName, &qty, &itemsPerDay, expirationDate);
    fclose(f);

    heap *itemHeap = heap_nova(1);
    elemento_t *item = elemento_novo(itemName, expirationDate, qty, itemsPerDay);
    if(!heap_insere(itemHeap, item))
    {
        printf("ERRO: heap_insere retornou NULL\n");
        elemento_apaga(item);
        avl_apaga(categAvl);
        categAvl = NULL;
        return 999;
    }

    category_t *categ = novaCategoria(itemHeap, categName);

    if(verifica_avl_insere(categAvl, categ) == -1)
        errCount++;

    if(verifica_avl_pesquisa(categAvl) == -1)
        errCount++;

    avl_apaga(categAvl);
    categAvl = NULL;

    return errCount;
}

int teste_artigo_adiciona_e_criar_montra(const char* file_name)
{
    printf("teste_artigo_adiciona_e_criar_montra iniciado...\n");
    int errCount = 0;
    FILE *f = fopen(file_name, "r");
    if(!f)
    {
        printf("ERRO: ficheiro %s nao encontrado\n", file_name);
        return 999;
    }
    arvore_avl *categAvl = avl_nova();
    if(!categAvl)
    {
        printf("ERRO: avl_nova retornou NULL\n");
        return 999;
    }

    int countPerCateg[N_CATEG] = {0};
    while(1)
    {
        char itemName[100], categName[MAX_CATEGNAME_LEN], expirationDate[11];
        int qty, itemsPerDay;
        if(fscanf(f, "%s %s %d %d %s\n",
                  itemName, categName, &qty, &itemsPerDay, expirationDate)==EOF) break;

        elemento_t *item = elemento_novo(itemName, expirationDate, qty, itemsPerDay);

        int itemCount = 0;
        for(int i=0; i<N_CATEG; i++)
        {
            if(!strcmp(categName, CATEGORIES[i]))
            {
                itemCount = countPerCateg[i];
                countPerCateg[i]++;
                break;
            }
        }

        if(verifica_artigo_adiciona(categAvl, item, categName, CAP_ALL_CATEG, itemCount, VERBOSITY))
        {
            errCount++;
            break;
        }
    }
    fclose(f);

    char categMontra[MAX_CATEGNAME_LEN] = "frescos";
    int numPorItemMontra = 5;
    int totalItensMontra = 10;
    int tamanhoEsperado = 3;
    if(verifica_criar_montra(categAvl, categMontra, numPorItemMontra,
                             totalItensMontra, tamanhoEsperado) == -1)
        errCount++;

    avl_apaga(categAvl);
    categAvl = NULL;

    return errCount;
}
/* ================================================= */


int main(int argc, char** argv)
{
    int errCount=0, err;
    const char *file_name = (argc > 1)? argv[1] : DEFAULT_FILE;

    err = teste_elemento_novo_e_metrica(file_name);
    if(err == 999)
    {
        printf("Os testes nao podem prosseguir devido a ERROS fatais\n");
        return -1;
    }
    else if(err)
    {
        printf("ERRO: %d erros encontrados em teste_elemento_novo_e_metrica\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: teste_elemento_novo_e_metrica passou\n\n");
    }

    err = teste_heap(file_name);
    if(err == 999)
    {
        printf("Os testes nao podem prosseguir devido a ERROS fatais\n");
        return -1;
    }
    if(err)
    {
        printf("ERRO: %d erros encontrados em teste_heap\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: teste_heap passou\n\n");
    }

    err = teste_avl(file_name);
    if(err == 999)
    {
        printf("Os testes nao podem prosseguir devido a ERROS fatais\n");
        return -1;
    }
    if(err)
    {
        printf("ERRO: %d erros encontrados em teste_avl\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: teste_avl passou\n\n");
    }

    err = teste_artigo_adiciona_e_criar_montra(file_name);
    if(err == 999)
    {
        printf("Os testes nao podem prosseguir devido a ERROS fatais\n");
        return -1;
    }
    if(err)
    {
        printf("ERRO: %d erros encontrados em teste_artigo_adiciona_e_criar_montra\n\n", err);
        errCount += err;
    }
    else
    {
        printf("OK: teste_artigo_adiciona_e_criar_montra passou\n\n");
    }

    if(errCount == 0)
        printf("FIM DOS TESTES: Todos os testes passaram\n");
    else
        printf("FIM DOS TESTES: Foram encontrados %d ERROS no total\n", errCount);

    return 0;

}
