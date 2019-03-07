#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"

#define MAX_STRING 500
#define PATH "IMDB.txt"

vetor *lerFicheiro(char *path)
{
    FILE *fin = fopen(path, "r");
    vetor *vec = vetor_novo();
    
    char temp[MAX_STRING];
    char *t;
    char *nome, *ano_str;
    int ano, votos;
    float classificacao;

    fgets(temp, MAX_STRING, fin);

    while(fscanf(fin, "%d %d %f", &ano, &votos, &classificacao) == 3)
    {
        t = temp;
        fgets(temp, MAX_STRING, fin);

        while(t[0] == ' ')
            t += 1;
        
        nome = strtok(t, "(");
        nome[strlen(nome) - 1] = '\0';
        ano_str = strtok(NULL, "(");
        ano_str[4] = '\0';
        ano = atoi(ano_str);
        vetor_insere(vec, nome, votos, classificacao, ano, vetor_tamanho(vec));
    }

    return vec;
}

void vetor_imprime(vetor *vec)
{
    for(int i = 0; i < vetor_tamanho(vec); i++)
        printf("[%d]\t%s\t%d\t%d\t%f\n", i, vec->elementos[i].titulo,
            vec->elementos[i].ano, vec->elementos[i].votos, vec->elementos[i].classificacao);
}

int main(int argc, char const *argv[])
{
    vetor *vec = lerFicheiro(PATH);
    vetor_imprime(vec);

    vetor_ordena_ano(vec);
    printf("Vetor Ordenado\n");
    vetor_imprime(vec);

    vetor *pesquisa = vetor_pesquisa_ano(vec, 2010);
    vetor_imprime(pesquisa);

    return 0;
}
