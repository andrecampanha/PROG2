#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "vetor.h"
#include "lista.h"

#define PATH "nomes.txt"
#define MAX_STRING 255
#define ITER 1000

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    vetor *vec = vetor_novo();
    lista *lst = lista_nova();
    
    FILE *fin = fopen(PATH, "r");
    char str[MAX_STRING];
    clock_t start_t, end_t;

    //----------------------------------

    start_t = clock();

    while(fscanf(fin, "%s", str) == 1)
    {
        vetor_insere(vec, str, vec->tamanho);
    }

    for(int i = 0; i < ITER; i++)
    {
        vetor_elemento(vec, rand() % vec->tamanho);
    }

    for(int i = 0; i < vec->tamanho; i++)
    {
        vetor_remove(vec, i);
    }

    fseek(fin, 0, SEEK_SET);

    while(fscanf(fin, "%s", str) == 1)
    {
        vetor_insere(vec, str, 0);
    }

    end_t = clock();
    printf("vetor: %.3f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

    // --------------------------------------------

    fseek(fin, 0, SEEK_SET);
    start_t = clock();

    while(fscanf(fin, "%s", str) == 1)
    {
        lista_insere(lst, str, NULL);
    }

    for(int i = 0; i < ITER; i++)
    {
        lista_elemento(lst, rand() % lst->tamanho);
    }

    for(int i = 0; i < lst->tamanho; i++)
    {
        lista_remove(lst, lista_elemento(lst, i));
    }

    fseek(fin, 0, SEEK_SET);

    while(fscanf(fin, "%s", str) == 1)
    {
        lista_insere(lst, str, lst->inicio);
    }

    end_t = clock();
    printf("lista: %.3f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
}
