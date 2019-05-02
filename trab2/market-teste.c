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
#define N_CATEG 4
#define CAP_ALL_CATEG 3

const char DEFAULT_FILE[32] = "armazem.txt";
const char CATEGORIES[N_CATEG][MAX_CATEGNAME_LEN] = {
    "frescos",
    "peixaria",
    "livros",
    "beleza"
};
/* ================================================= */

/* VERIFICACOES IMPLEMENTADAS */
int verifica_elemento_novo(elemento_t **elem, const char* nameItem, const char* expDate, int qty, int sellRate)
{
    *elem = elemento_novo(nameItem, expDate, qty, sellRate);
    if(!(*elem))
    {
        printf("verifica_elemento_novo: Erro na função elemento_novo (retornou NULL)\n");
        return -1;
    }

    if(strcmp((*elem)->nameItem, nameItem))
    {
        printf("verifica_elemento_novo: Erro na função elemento_novo (nameItem e' %s)", (*elem)->nameItem);
        return -1;
    }

    return 0;
}

int verifica_metrica(elemento_t *elem)
{
    float metrica = calcMetrica(elem);
    if(metrica <= 0. || metrica >= 1.)
    {
        printf("verifica_metrica: Erro na função calcMetrica, o valor retornado deve estar em (0, 1) (retornou %f)\n", metrica);
        return -1;
    }

    return 0;
}

int verifica_heap_nova(heap **h, int capacidade)
{
    *h = heap_nova(capacidade);
    if(!(*h))
    {
        printf("verifica_heap_nova: Erro na função heap_nova (retornou NULL)\n");
        return -1;
    }

    if((*h)->tamanho != 0)
    {
        printf("verifica_heap_nova: Erro na função heap_nova (tamanho da heap e' %d)\n", (*h)->tamanho);
        return -1;
    }

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
            printf("verifica_heap_remove: Erro na função heap_remove (retornou NULL)\n");
            return -1;
        }
        elemento_apaga(elem);
        elem = NULL;
        if(h->tamanho == tamanho_ini)
        {
            printf("verifica_heap_remove: Erro na função heap_remove (tamanho da heap manteve-se)\n");
            return -1;
        }
    }

    return 0;
}

int verifica_avl_insere(arvore_avl *avl, category_t* categ)
{
    avl->raiz = avl_insere(avl->raiz , categ);
    if(!avl->raiz)
    {
        printf("verifica_avl_insere: Erro na função avl_insere (retornou NULL)\n");
        return -1;
    }
    if(!(avl->raiz->categ))
    {
        printf("verifica_avl_insere: Erro na função avl_insere (no->categ e' NULL)\n");
        return -1;
    }

    return 0;
}

int verifica_avl_pesquisa(arvore_avl *avl)
{
    char categQuery[MAX_CATEGNAME_LEN];
    strcpy(categQuery, avl->raiz->categ->categName);

    no_avl *resultado = avl_pesquisa(avl->raiz, categQuery);
    if(!resultado)
    {
        printf("verifica_avl_pesquisa: Erro na função avl_pesquisa (retornou NULL)\n");
        return -1;
    }
    if(strcmp(resultado->categ->categName, categQuery))
    {
        printf("verifica_avl_pesquisa: Erro na função avl_pesquisa (nome da categoria retornado != pesquisado)\n");
        return -1;
    }

    return 0;
}

int verifica_artigo_adiciona(arvore_avl *avl, elemento_t *elem,  char *categName, int capCateg, int itemCount)
{
    if(!avl->raiz)
    {
        artigo_adiciona(avl, elem, categName, capCateg);
        if(!avl->raiz)
        {
            printf("verifica_artigo_adiciona: AVL continua vazia apos insercao de artigo\n");
            return -1;
        }
    }
    else if(itemCount < capCateg)
    {
        if(artigo_adiciona(avl, elem, categName, capCateg) == 0)
        {
            printf("verifica_artigo_adiciona: Erro na função artigo_adiciona (retornou 0)\n");
            return -1;
        }
    }
    else
    {
        if(artigo_adiciona(avl, elem, categName, capCateg) == 1)
        {
            printf("verifica_artigo_adiciona: Erro na função artigo_adiciona (capacidade excedida e retornou 1)\n");
            return -1;
        }
        else
        {
            elemento_apaga(elem);
            elem = NULL;
        }
    }

    return 0;
}

int verifica_criar_montra(arvore_avl *avl, char *categName, int numPorItem, int totalItens, int tamanhoEsp)
{
    int array_tamanho;
    elemento_t **itens = criar_montra(avl, categName, numPorItem, totalItens, &array_tamanho);
    for(int i = 0; i < array_tamanho; i++)
    {
        elemento_apaga(itens[i]);
        itens[i] = NULL;
    }
    free(itens);
    itens = NULL;

    if(array_tamanho != tamanhoEsp)
    {
        printf("verifica_criar_montra: tamanho do array retornado diferente do esperado (tamanho retornado: %d))\n", array_tamanho);
        return -1;
    }

    return 0;
}
/* ================================================= */


/* DEFINICAO DOS CENARIOS DE TESTE */
int teste_elemento_novo_e_metrica(const char *file_name)
{
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

        int itemCount;
        for(int i=0; i<N_CATEG; i++)
        {
            if(!strcmp(categName, CATEGORIES[i]))
            {
                itemCount = countPerCateg[i];
                countPerCateg[i]++;
            }
        }

        if(verifica_artigo_adiciona(categAvl, item, categName, CAP_ALL_CATEG, itemCount))
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

    if(errCount==0)
        printf("FIM DOS TESTES: Todos os testes passaram\n");
    else
        printf("FIM DOS TESTES: Foram encontrados %d ERROS no total\n", errCount);

    return 0;

}
