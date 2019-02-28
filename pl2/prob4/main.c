#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vetor.h"

#define MAX_STRING 500
#define N_STRINGS 5


void ler_string(char *string)
{
    fgets(string, MAX_STRING, stdin);
    string[strlen(string) - 1] = '\0';
}

void imprime_vetor(vetor *v)
{
    for(int i = 0; i < vetor_tamanho(v); i++)
    {
        printf("[%d] %s\n", i, vetor_elemento(v, i));
    }
}

int main()
{
    int i;
    vetor *v = vetor_novo();
    vetor *v2 = vetor_novo();

    vetor_insere(v2, "adicionado", 0);
    vetor_insere(v2, "adicionado2", 1);

    char temp[MAX_STRING];
    for(i = 0; i < N_STRINGS; i++)
    {
        printf("Introduza a %dª string: ", i + 1);
        ler_string(temp);
        vetor_insere(v, temp, i);        
    }
    imprime_vetor(v);

    printf("\nIntroduza a string a apagar: ");
    ler_string(temp);

    i = vetor_pesquisa(v, temp);
    if(i == -1)
        printf("String não existe!\n");
    else
        vetor_remove(v, i);

    imprime_vetor(v);

    vetor_ordena(v);
    printf("\nVetor ordenado:\n");
    imprime_vetor(v);

    v = vetor_concatena(v, v2);
    printf("\nVetor concatenado:\n");
    imprime_vetor(v);

    vetor_inverte(v);
    printf("\nVetor invertido:\n");
    imprime_vetor(v);

    v = vetor_baralha(v);
    printf("\nVetor baralhado:\n");
    imprime_vetor(v);
}